#include <TestFrameworkPCH.h>

#include <Foundation/IO/FileSystem/FileReader.h>
#include <Foundation/Logging/VisualStudioWriter.h>
#include <Foundation/Utilities/StackTracer.h>
#include <TestFramework/Utilities/TestOrder.h>

#ifdef EZ_TESTFRAMEWORK_USE_FILESERVE
#  include <FileservePlugin/Client/FileserveClient.h>
#  include <FileservePlugin/Client/FileserveDataDir.h>
#  include <FileservePlugin/FileservePluginDLL.h>
#endif

ezTestFramework* ezTestFramework::s_pInstance = nullptr;

const char* ezTestFramework::s_szTestBlockName = "";
int ezTestFramework::s_iAssertCounter = 0;
bool ezTestFramework::s_bCallstackOnAssert = false;

static void PrintCallstack(const char* szText)
{
  printf("%s", szText);
#if EZ_ENABLED(EZ_PLATFORM_WINDOWS)
  OutputDebugStringW(ezStringWChar(szText).GetData());
#endif
  fflush(stdout);
  fflush(stderr);
};

static bool TestAssertHandler(const char* szSourceFile, ezUInt32 uiLine, const char* szFunction, const char* szExpression,
                              const char* szAssertMsg)
{
  if (ezTestFramework::s_bCallstackOnAssert)
  {
    void* pBuffer[64];
    ezArrayPtr<void*> tempTrace(pBuffer);
    const ezUInt32 uiNumTraces = ezStackTracer::GetStackTrace(tempTrace, nullptr);
    ezStackTracer::ResolveStackTrace(tempTrace.GetSubArray(0, uiNumTraces), &PrintCallstack);
  }
  ezTestFramework::Error(szExpression, szSourceFile, (ezInt32)uiLine, szFunction, szAssertMsg);

#if EZ_ENABLED(EZ_PLATFORM_WINDOWS)
  // if a debugger is attached, one typically always wants to know about asserts
  if (IsDebuggerPresent())
    return true;
#endif

  return ezTestFramework::GetAssertOnTestFail();
}

////////////////////////////////////////////////////////////////////////
// ezTestFramework public functions
////////////////////////////////////////////////////////////////////////

ezTestFramework::ezTestFramework(const char* szTestName, const char* szAbsTestOutputDir, const char* szRelTestDataDir, int argc,
                                 const char** argv)
    : m_sTestName(szTestName)
    , m_sAbsTestOutputDir(szAbsTestOutputDir)
    , m_sRelTestDataDir(szRelTestDataDir)
{
  s_pInstance = this;

  ezCommandLineUtils::GetGlobalInstance()->SetCommandLine(argc, argv);

  GetTestSettingsFromCommandLine(argc, argv);
}

ezTestFramework::~ezTestFramework()
{
  if (m_bIsInitialized)
    DeInitialize();
  s_pInstance = nullptr;
}

void ezTestFramework::Initialize()
{
  // Don't do this, it will spam the log with sub-system messages
  // ezGlobalLog::AddLogWriter(ezLogWriter::Console::LogMessageHandler);
  // ezGlobalLog::AddLogWriter(ezLogWriter::VisualStudio::LogMessageHandler);

  ezStartup::AddApplicationTag("testframework");
  ezStartup::StartupCoreSystems();

  // if tests need to write data back through Fileserve (e.g. image comparison results), they can do that through a data dir mounted with
  // this path
  ezFileSystem::SetSpecialDirectory("eztest", ezTestFramework::GetInstance()->GetAbsOutputPath());

  CreateOutputFolder();

  // figure out which tests exist
  GatherAllTests();

  // load the test order from file, if that file does not exist, the array is not modified
  LoadTestOrder();

  // save the current order back to the same file
  AutoSaveTestOrder();

  m_bIsInitialized = true;

  ezFileSystem::DetectSdkRootDirectory();
}

void ezTestFramework::DeInitialize()
{
  m_bIsInitialized = false;
}

const char* ezTestFramework::GetTestName() const
{
  return m_sTestName.c_str();
}

const char* ezTestFramework::GetAbsOutputPath() const
{
  return m_sAbsTestOutputDir.c_str();
}


const char* ezTestFramework::GetRelTestDataPath() const
{
  return m_sRelTestDataDir.c_str();
}


const char* ezTestFramework::GetAbsTestSettingsFilePath() const
{
  return m_sAbsTestSettingsFilePath.c_str();
}

void ezTestFramework::RegisterOutputHandler(OutputHandler Handler)
{
  // do not register a handler twice
  for (ezUInt32 i = 0; i < m_OutputHandlers.size(); ++i)
  {
    if (m_OutputHandlers[i] == Handler)
      return;
  }

  m_OutputHandlers.push_back(Handler);
}

bool ezTestFramework::GetAssertOnTestFail()
{
#if EZ_ENABLED(EZ_PLATFORM_WINDOWS)
  if (!IsDebuggerPresent())
    return false;
#endif

  return s_pInstance->m_Settings.m_bAssertOnTestFail;
}

void ezTestFramework::GatherAllTests()
{
  m_TestEntries.clear();

  m_iErrorCount = 0;
  m_iTestsFailed = 0;
  m_iTestsPassed = 0;
  m_iExecutingTest = -1;
  m_iExecutingSubTest = -1;
  m_bSubTestInitialized = false;

  // first let all simple tests register themselves
  {
    ezRegisterSimpleTestHelper* pHelper = ezRegisterSimpleTestHelper::GetFirstInstance();

    while (pHelper)
    {
      pHelper->RegisterTest();

      pHelper = pHelper->GetNextInstance();
    }
  }

  ezTestConfiguration config;
  ezTestBaseClass* pTestClass = ezTestBaseClass::GetFirstInstance();

  while (pTestClass)
  {
    pTestClass->ClearSubTests();
    pTestClass->SetupSubTests();
    pTestClass->UpdateConfiguration(config);

    ezTestEntry e;
    e.m_pTest = pTestClass;
    e.m_szTestName = pTestClass->GetTestName();

    for (ezUInt32 i = 0; i < pTestClass->m_Entries.size(); ++i)
    {
      ezSubTestEntry st;
      st.m_szSubTestName = pTestClass->m_Entries[i].m_szName;
      st.m_iSubTestIdentifier = pTestClass->m_Entries[i].m_iIdentifier;

      e.m_SubTests.push_back(st);
    }

    m_TestEntries.push_back(e);

    pTestClass = pTestClass->GetNextInstance();
  }
  ::SortTestsAlphabetically(m_TestEntries);

  m_Result.SetupTests(m_TestEntries, config);
}

void ezTestFramework::GetTestSettingsFromCommandLine(int argc, const char** argv)
{
  // use a local instance of ezCommandLineUtils as global instance is not guaranteed to have been set up
  // for all call sites of this method.
  ezCommandLineUtils cmd;
  cmd.SetCommandLine(argc, argv);

  m_Settings.m_bRunTests = cmd.GetBoolOption("-run", false);
  m_Settings.m_bCloseOnSuccess = cmd.GetBoolOption("-close", false);
  m_Settings.m_bNoGUI = cmd.GetBoolOption("-nogui", false);

  m_Settings.m_bAssertOnTestFail = cmd.GetBoolOption("-assert", m_Settings.m_bAssertOnTestFail);
  m_Settings.m_bOpenHtmlOutput = cmd.GetBoolOption("-html", m_Settings.m_bOpenHtmlOutput);
  m_Settings.m_bKeepConsoleOpen = cmd.GetBoolOption("-console", m_Settings.m_bKeepConsoleOpen);
  m_Settings.m_bShowMessageBox = cmd.GetBoolOption("-msgbox", m_Settings.m_bShowMessageBox);
  m_Settings.m_iRevision = cmd.GetIntOption("-rev", -1);
  m_Settings.m_bEnableAllTests = cmd.GetBoolOption("-all", false);
  m_Settings.m_uiFullPasses = cmd.GetIntOption("-passes", 1, false);

  if (cmd.GetStringOptionArguments("-json") == 1)
    m_Settings.m_sJsonOutput = cmd.GetStringOption("-json", 0, "");

  if (cmd.GetStringOptionArguments("-settings") == 1)
  {
    m_sAbsTestSettingsFilePath = cmd.GetStringOption("-settings", 0, "");
    // If a custom settings file was provided, default to -nosave as to not overwrite that file with additional
    // parameters from command line. Use "-nosave false" to explicitely enable auto save in this case.
    m_Settings.m_bNoAutomaticSaving = cmd.GetBoolOption("-nosave", true);
  }
  else
  {
    m_sAbsTestSettingsFilePath = m_sAbsTestOutputDir + std::string("/TestSettings.txt");
    m_Settings.m_bNoAutomaticSaving = cmd.GetBoolOption("-nosave", false);
  }

  m_uiPassesLeft = m_Settings.m_uiFullPasses;
}

void ezTestFramework::LoadTestOrder()
{
  ::LoadTestOrder(m_sAbsTestSettingsFilePath.c_str(), m_TestEntries, m_Settings);
  if (m_Settings.m_bEnableAllTests)
    SetAllTestsEnabledStatus(true);
}

void ezTestFramework::CreateOutputFolder()
{
  ezOSFile::CreateDirectoryStructure(m_sAbsTestOutputDir.c_str());

  EZ_ASSERT_RELEASE(ezOSFile::ExistsDirectory(m_sAbsTestOutputDir.c_str()), "Failed to create output directory '{0}'",
                    m_sAbsTestOutputDir.c_str());
}

void ezTestFramework::AutoSaveTestOrder()
{
  if (m_Settings.m_bNoAutomaticSaving)
    return;

  SaveTestOrder(m_sAbsTestSettingsFilePath.c_str());
}


void ezTestFramework::SaveTestOrder(const char* const filePath)
{
  ::SaveTestOrder(filePath, m_TestEntries, m_Settings);
}

void ezTestFramework::SetAllTestsEnabledStatus(bool bEnable)
{
  const ezUInt32 uiTestCount = GetTestCount();
  for (ezUInt32 uiTestIdx = 0; uiTestIdx < uiTestCount; ++uiTestIdx)
  {
    m_TestEntries[uiTestIdx].m_bEnableTest = bEnable;
    const ezUInt32 uiSubTestCount = (ezUInt32)m_TestEntries[uiTestIdx].m_SubTests.size();
    for (ezUInt32 uiSubTest = 0; uiSubTest < uiSubTestCount; ++uiSubTest)
    {
      m_TestEntries[uiTestIdx].m_SubTests[uiSubTest].m_bEnableTest = bEnable;
    }
  }
}

void ezTestFramework::SetAllFailedTestsEnabledStatus()
{
  const auto& LastResult = GetTestResult();

  const ezUInt32 uiTestCount = GetTestCount();
  for (ezUInt32 uiTestIdx = 0; uiTestIdx < uiTestCount; ++uiTestIdx)
  {
    const auto& TestRes = LastResult.GetTestResultData(uiTestIdx, -1);
    m_TestEntries[uiTestIdx].m_bEnableTest = TestRes.m_bExecuted && !TestRes.m_bSuccess;

    const ezUInt32 uiSubTestCount = (ezUInt32)m_TestEntries[uiTestIdx].m_SubTests.size();
    for (ezUInt32 uiSubTest = 0; uiSubTest < uiSubTestCount; ++uiSubTest)
    {
      const auto& SubTestRes = LastResult.GetTestResultData(uiTestIdx, uiSubTest);
      m_TestEntries[uiTestIdx].m_SubTests[uiSubTest].m_bEnableTest = SubTestRes.m_bExecuted && !SubTestRes.m_bSuccess;
    }
  }
}

void ezTestFramework::ResetTests()
{
  m_iErrorCount = 0;
  m_iTestsFailed = 0;
  m_iTestsPassed = 0;
  m_iExecutingTest = -1;
  m_iExecutingSubTest = -1;
  m_bSubTestInitialized = false;
  m_bAbortTests = false;

  m_Result.Reset();
}

ezTestAppRun ezTestFramework::RunTestExecutionLoop()
{
  if (!m_bIsInitialized)
  {
    Initialize();

#ifdef EZ_TESTFRAMEWORK_USE_FILESERVE
    if (ezFileserveClient::GetSingleton() == nullptr)
    {
      EZ_DEFAULT_NEW(ezFileserveClient);

      if (ezFileserveClient::GetSingleton()->SearchForServerAddress().Failed())
      {
        ezFileserveClient::GetSingleton()->WaitForServerInfo();
      }
    }

    if (ezFileserveClient::GetSingleton()->EnsureConnected(ezTime::Seconds(-30)).Failed())
    {
      Error("Failed to establish a Fileserve connection", "", 0, "ezTestFramework::RunTestExecutionLoop", "");
      return ezTestAppRun::Quit;
    }
#endif
  }

#ifdef EZ_TESTFRAMEWORK_USE_FILESERVE
  ezFileserveClient::GetSingleton()->UpdateClient();
#endif


  if (m_iExecutingTest < 0)
  {
    StartTests();
    m_iExecutingTest = 0;
    EZ_ASSERT_DEV(m_iExecutingSubTest == -1, "Invalid test framework state");
    EZ_ASSERT_DEV(!m_bSubTestInitialized, "Invalid test framework state");
  }

  ExecuteNextTest();

  if (m_iExecutingTest >= (ezInt32)m_TestEntries.size())
  {
    EndTests();

    if (m_uiPassesLeft > 1 && !m_bAbortTests)
    {
      --m_uiPassesLeft;

      m_iExecutingTest = -1;
      m_iExecutingSubTest = -1;

      return ezTestAppRun::Continue;
    }

#ifdef EZ_TESTFRAMEWORK_USE_FILESERVE
    if (ezFileserveClient* pClient = ezFileserveClient::GetSingleton())
    {
      // shutdown the fileserve client
      EZ_DEFAULT_DELETE(pClient);
    }
#endif

    return ezTestAppRun::Quit;
  }

  return ezTestAppRun::Continue;
}

void ezTestFramework::StartTests()
{
  ResetTests();
  m_bTestsRunning = true;

  ezTestFramework::Output(ezTestOutput::StartOutput, "");

  m_PreviousAssertHandler = ezGetAssertHandler();

  ezSetAssertHandler(TestAssertHandler);
}

// Redirects engine warnings / errors to test-framework output
static void LogWriter(const ezLoggingEventData& e)
{
  switch (e.m_EventType)
  {
    case ezLogMsgType::ErrorMsg:
      ezTestFramework::Output(ezTestOutput::Error, "ezLog Error: %s", e.m_szText);
      break;
    case ezLogMsgType::SeriousWarningMsg:
      ezTestFramework::Output(ezTestOutput::Error, "ezLog Serious Warning: %s", e.m_szText);
      break;
    case ezLogMsgType::WarningMsg:
      ezTestFramework::Output(ezTestOutput::Warning, "ezLog Warning: %s", e.m_szText);
      break;
    case ezLogMsgType::InfoMsg:
    case ezLogMsgType::DevMsg:
    case ezLogMsgType::DebugMsg:
    {
      if (ezStringUtils::IsEqual_NoCase(e.m_szTag, "test"))
        ezTestFramework::Output(ezTestOutput::Details, e.m_szText);
    }
    break;

    default:
      return;
  }
}

void ezTestFramework::ExecuteNextTest()
{
  EZ_ASSERT_DEV(m_iExecutingTest >= 0, "Invalid current test.");

  if (m_iExecutingTest == (ezInt32)GetTestCount())
    return;

  if (!m_TestEntries[m_iExecutingTest].m_bEnableTest)
  {
    // next time run the next test and start with the first subtest
    m_iExecutingTest++;
    m_iExecutingSubTest = -1;
    return;
  }

  ezTestEntry& TestEntry = m_TestEntries[m_iExecutingTest];
  ezTestBaseClass* pTestClass = m_TestEntries[m_iExecutingTest].m_pTest;

  // Execute test
  {
    if (m_iExecutingSubTest == -1) // no subtest has run yet, so initialize the test first
    {
      if (m_bAbortTests)
      {
        m_iExecutingTest = (ezInt32)m_TestEntries.size(); // skip to the end of all tests
        m_iExecutingSubTest = -1;
        return;
      }

      m_iExecutingSubTest = 0;
      m_fTotalTestDuration = 0.0;

      // Reset assert counter. This variable is used to reduce the overhead of counting millions of asserts.
      s_iAssertCounter = 0;
      m_iCurrentTestIndex = m_iExecutingTest;
      // Log writer translates engine warnings / errors into test framework error messages.
      ezGlobalLog::AddLogWriter(LogWriter);

      m_iErrorCountBeforeTest = GetTotalErrorCount();

      ezTestFramework::Output(ezTestOutput::BeginBlock, "Executing Test: '%s'", TestEntry.m_szTestName);

      // *** Test Initialization ***
      if (pTestClass->DoTestInitialization().Failed())
      {
        m_iExecutingSubTest = (ezInt32)TestEntry.m_SubTests.size(); // make sure all subtests are skipped
      }
    }

    if (m_iExecutingSubTest < (ezInt32)TestEntry.m_SubTests.size())
    {
      ezSubTestEntry& subTest = TestEntry.m_SubTests[m_iExecutingSubTest];
      ezInt32 iSubTestIdentifier = subTest.m_iSubTestIdentifier;

      if (!subTest.m_bEnableTest)
      {
        ++m_iExecutingSubTest;
        return;
      }

      if (!m_bSubTestInitialized)
      {
        if (m_bAbortTests)
        {
          // tests shall be aborted, so do not start a new one

          m_iExecutingTest = (ezInt32)m_TestEntries.size(); // skip to the end of all tests
          m_iExecutingSubTest = -1;
          return;
        }

        m_fTotalSubTestDuration = 0.0;
        m_uiSubTestInvocationCount = 0;

        // First flush of assert counter, these are all asserts during test init.
        FlushAsserts();
        m_iCurrentSubTestIndex = m_iExecutingSubTest;
        ezTestFramework::Output(ezTestOutput::BeginBlock, "Executing Sub-Test: '%s'", subTest.m_szSubTestName);

        // *** Sub-Test Initialization ***
        m_bSubTestInitialized = pTestClass->DoSubTestInitialization(iSubTestIdentifier).Succeeded();
      }

      ezTestAppRun subTestResult = ezTestAppRun::Quit;

      if (m_bSubTestInitialized)
      {
        // *** Run Sub-Test ***
        double fDuration = 0.0;

        // start with 1
        ++m_uiSubTestInvocationCount;

        subTestResult = pTestClass->DoSubTestRun(iSubTestIdentifier, fDuration, m_uiSubTestInvocationCount);

        if (m_bImageComparisonScheduled)
        {
          EZ_TEST_IMAGE(m_uiComparisonImageNumber, m_uiMaxImageComparisonError);
          m_bImageComparisonScheduled = false;
        }

        // I guess we can require that tests are written in a way that they can be interrupted
        if (m_bAbortTests)
          subTestResult = ezTestAppRun::Quit;

        m_fTotalSubTestDuration += fDuration;
      }

      // this is executed when sub-test initialization failed or the sub-test reached its end
      if (subTestResult == ezTestAppRun::Quit)
      {
        // *** Sub-Test De-Initialization ***
        pTestClass->DoSubTestDeInitialization(iSubTestIdentifier);

        bool bSubTestSuccess = m_bSubTestInitialized && (m_Result.GetErrorMessageCount(m_iExecutingTest, m_iExecutingSubTest) == 0);
        ezTestFramework::TestResult(m_iExecutingSubTest, bSubTestSuccess, m_fTotalSubTestDuration);

        m_fTotalTestDuration += m_fTotalSubTestDuration;

        // advance to the next (sub) test
        m_bSubTestInitialized = false;
        ++m_iExecutingSubTest;

        // Second flush of assert counter, these are all asserts for the current subtest.
        FlushAsserts();
        ezTestFramework::Output(ezTestOutput::EndBlock, "");
        m_iCurrentSubTestIndex = -1;
      }
    }

    if (m_iExecutingSubTest >= (ezInt32)TestEntry.m_SubTests.size())
    {
      // *** Test De-Initialization ***
      pTestClass->DoTestDeInitialization();
      // Third and last flush of assert counter, these are all asserts for the test de-init.
      FlushAsserts();

      ezGlobalLog::RemoveLogWriter(LogWriter);

      bool bTestSuccess = m_iErrorCountBeforeTest == GetTotalErrorCount();
      ezTestFramework::TestResult(-1, bTestSuccess, m_fTotalTestDuration);
      ezTestFramework::Output(ezTestOutput::EndBlock, "");
      m_iCurrentTestIndex = -1;

      // advance to the next test
      m_iExecutingTest++;
      m_iExecutingSubTest = -1;
    }
  }
}

void ezTestFramework::EndTests()
{
  ezSetAssertHandler(m_PreviousAssertHandler);
  m_PreviousAssertHandler = nullptr;

  m_bTestsRunning = false;
  if (GetTestsFailedCount() == 0)
    ezTestFramework::Output(ezTestOutput::FinalResult, "All tests passed.");
  else
    ezTestFramework::Output(ezTestOutput::FinalResult, "Tests failed: %i. Tests passed: %i", GetTestsFailedCount(), GetTestsPassedCount());

  if (!m_Settings.m_sJsonOutput.empty())
    m_Result.WriteJsonToFile(m_Settings.m_sJsonOutput.c_str());

  m_iExecutingTest = -1;
  m_iExecutingSubTest = -1;
  m_bAbortTests = false;
}

void ezTestFramework::AbortTests()
{
  m_bAbortTests = true;
}

ezUInt32 ezTestFramework::GetTestCount() const
{
  return (ezUInt32)m_TestEntries.size();
}

ezUInt32 ezTestFramework::GetTestEnabledCount() const
{
  ezUInt32 uiEnabledCount = 0;
  const ezUInt32 uiTests = GetTestCount();
  for (ezUInt32 uiTest = 0; uiTest < uiTests; ++uiTest)
  {
    uiEnabledCount += m_TestEntries[uiTest].m_bEnableTest ? 1 : 0;
  }
  return uiEnabledCount;
}

ezUInt32 ezTestFramework::GetSubTestEnabledCount(ezUInt32 uiTestIndex) const
{
  if (uiTestIndex >= GetTestCount())
    return 0;

  ezUInt32 uiEnabledCount = 0;
  const ezUInt32 uiSubTests = (ezUInt32)m_TestEntries[uiTestIndex].m_SubTests.size();
  for (ezUInt32 uiSubTest = 0; uiSubTest < uiSubTests; ++uiSubTest)
  {
    uiEnabledCount += m_TestEntries[uiTestIndex].m_SubTests[uiSubTest].m_bEnableTest ? 1 : 0;
  }
  return uiEnabledCount;
}

bool ezTestFramework::IsTestEnabled(ezUInt32 uiTestIndex) const
{
  if (uiTestIndex >= GetTestCount())
    return false;

  return m_TestEntries[uiTestIndex].m_bEnableTest;
}

bool ezTestFramework::IsSubTestEnabled(ezUInt32 uiTestIndex, ezUInt32 uiSubTestIndex) const
{
  if (uiTestIndex >= GetTestCount())
    return false;

  const ezUInt32 uiSubTests = (ezUInt32)m_TestEntries[uiTestIndex].m_SubTests.size();
  if (uiSubTestIndex >= uiSubTests)
    return false;

  return m_TestEntries[uiTestIndex].m_SubTests[uiSubTestIndex].m_bEnableTest;
}

void ezTestFramework::SetTestEnabled(ezUInt32 uiTestIndex, bool bEnabled)
{
  if (uiTestIndex >= GetTestCount())
    return;

  m_TestEntries[uiTestIndex].m_bEnableTest = bEnabled;
}

void ezTestFramework::SetSubTestEnabled(ezUInt32 uiTestIndex, ezUInt32 uiSubTestIndex, bool bEnabled)
{
  if (uiTestIndex >= GetTestCount())
    return;

  const ezUInt32 uiSubTests = (ezUInt32)m_TestEntries[uiTestIndex].m_SubTests.size();
  if (uiSubTestIndex >= uiSubTests)
    return;

  m_TestEntries[uiTestIndex].m_SubTests[uiSubTestIndex].m_bEnableTest = bEnabled;
}

ezTestEntry* ezTestFramework::GetTest(ezUInt32 uiTestIndex)
{
  if (uiTestIndex >= GetTestCount())
    return nullptr;

  return &m_TestEntries[uiTestIndex];
}

TestSettings ezTestFramework::GetSettings() const
{
  return m_Settings;
}

void ezTestFramework::SetSettings(const TestSettings& settings)
{
  m_Settings = settings;
}

ezTestFrameworkResult& ezTestFramework::GetTestResult()
{
  return m_Result;
}

ezInt32 ezTestFramework::GetTotalErrorCount() const
{
  return m_iErrorCount;
}

ezInt32 ezTestFramework::GetTestsPassedCount() const
{
  return m_iTestsPassed;
}

ezInt32 ezTestFramework::GetTestsFailedCount() const
{
  return m_iTestsFailed;
}

double ezTestFramework::GetTotalTestDuration() const
{
  return m_Result.GetTotalTestDuration();
}

////////////////////////////////////////////////////////////////////////
// ezTestFramework protected functions
////////////////////////////////////////////////////////////////////////

static bool g_bBlockOutput = false;

void ezTestFramework::OutputImpl(ezTestOutput::Enum Type, const char* szMsg)
{
  if (Type == ezTestOutput::Error)
  {
    m_iErrorCount++;
  }
  // pass the output to all the registered output handlers, which will then write it to the console, file, etc.
  for (ezUInt32 i = 0; i < m_OutputHandlers.size(); ++i)
  {
    m_OutputHandlers[i](Type, szMsg);
  }

  if (g_bBlockOutput)
    return;

  m_Result.TestOutput(m_iCurrentTestIndex, m_iCurrentSubTestIndex, Type, szMsg);
}

void ezTestFramework::ErrorImpl(const char* szError, const char* szFile, ezInt32 iLine, const char* szFunction, const char* szMsg)
{
  m_Result.TestError(m_iCurrentTestIndex, m_iCurrentSubTestIndex, szError, ezTestFramework::s_szTestBlockName, szFile, iLine, szFunction,
                     szMsg);

  g_bBlockOutput = true;
  ezTestFramework::Output(ezTestOutput::Error, szError); // This will also increase the global error count.
  ezTestFramework::Output(ezTestOutput::BeginBlock, "");
  {
    if ((ezTestFramework::s_szTestBlockName != nullptr) && (ezTestFramework::s_szTestBlockName[0] != '\0'))
      ezTestFramework::Output(ezTestOutput::Message, "Block: '%s'", ezTestFramework::s_szTestBlockName);

    ezTestFramework::Output(ezTestOutput::ImportantInfo, "File: %s", szFile);
    ezTestFramework::Output(ezTestOutput::ImportantInfo, "Line: %i", iLine);
    ezTestFramework::Output(ezTestOutput::ImportantInfo, "Function: %s", szFunction);

    if ((szMsg != nullptr) && (szMsg[0] != '\0'))
      ezTestFramework::Output(ezTestOutput::Message, "Message: %s", szMsg);
  }
  ezTestFramework::Output(ezTestOutput::EndBlock, "");
  g_bBlockOutput = false;
}

void ezTestFramework::TestResultImpl(ezInt32 iSubTestIndex, bool bSuccess, double fDuration)
{
  m_Result.TestResult(m_iCurrentTestIndex, iSubTestIndex, bSuccess, fDuration);

  const ezUInt32 uiMin = (ezUInt32)(fDuration / 1000.0 / 60.0);
  const ezUInt32 uiSec = (ezUInt32)(fDuration / 1000.0 - uiMin * 60.0);
  const ezUInt32 uiMS = (ezUInt32)(fDuration - uiSec * 1000.0);

  ezTestFramework::Output(ezTestOutput::Duration, "%i:%02i:%03i", uiMin, uiSec, uiMS);

  if (iSubTestIndex == -1)
  {
    const char* szTestName = m_TestEntries[m_iCurrentTestIndex].m_szTestName;
    if (bSuccess)
    {
      m_iTestsPassed++;
      ezTestFramework::Output(ezTestOutput::Success, "Test '%s' succeeded", szTestName);
    }
    else
    {
      m_iTestsFailed++;
      ezTestFramework::Output(ezTestOutput::Error, "Test '%s' failed: %i Errors.", szTestName,
                              (ezUInt32)m_Result.GetErrorMessageCount(m_iCurrentTestIndex, iSubTestIndex));
    }
  }
  else
  {
    const char* szSubTestName = m_TestEntries[m_iCurrentTestIndex].m_SubTests[iSubTestIndex].m_szSubTestName;
    if (bSuccess)
    {
      ezTestFramework::Output(ezTestOutput::Success, "Sub-Test '%s' succeeded.", szSubTestName);
    }
    else
    {
      ezTestFramework::Output(ezTestOutput::Error, "Sub-Test '%s' failed: %i Errors.", szSubTestName,
                              (ezUInt32)m_Result.GetErrorMessageCount(m_iCurrentTestIndex, iSubTestIndex));
    }
  }
}

void ezTestFramework::FlushAsserts()
{
  m_Result.AddAsserts(m_iCurrentTestIndex, m_iCurrentSubTestIndex, s_iAssertCounter);
  s_iAssertCounter = 0;
}

void ezTestFramework::ScheduleImageComparison(ezUInt32 uiImageNumber, ezUInt32 uiMaxError)
{
  m_bImageComparisonScheduled = true;
  m_uiMaxImageComparisonError = uiMaxError;
  m_uiComparisonImageNumber = uiImageNumber;
}

void ezTestFramework::GenerateComparisonImageName(ezUInt32 uiImageNumber, ezStringBuilder& sImgName)
{
  const char* szTestName = GetTest(GetCurrentTestIndex())->m_szTestName;
  const char* szSubTestName = GetTest(GetCurrentTestIndex())->m_SubTests[GetCurrentSubTestIndex()].m_szSubTestName;

  sImgName.Format("{0}_{1}_{2}", szTestName, szSubTestName, ezArgI(uiImageNumber, 3, true));
  sImgName.ReplaceAll(" ", "_");
}

void ezTestFramework::GetCurrentComparisonImageName(ezStringBuilder& sImgName)
{
  GenerateComparisonImageName(m_uiComparisonImageNumber, sImgName);
}

static bool PerformImageComparison(ezStringBuilder sImgName, const ezImage& img, ezUInt32 uiMaxError, char* szErrorMsg)
{
  ezImage imgRGB;
  if (ezImageConversion::Convert(img, imgRGB, ezImageFormat::B8G8R8_UNORM).Failed())
  {
    safeprintf(szErrorMsg, 512, "Captured Image '%s' could not be converted to BGR8", sImgName.GetData());
    return false;
  }

  ezStringBuilder sImgPathReference, sImgPathResult;
  sImgPathReference.Format("Images_Reference/{0}.png", sImgName);
  sImgPathResult.Format(":imgout/Images_Result/{0}.png", sImgName);

  ezImage imgExp, imgExpRGB;
  if (imgExp.LoadFrom(sImgPathReference).Failed())
  {
    imgRGB.SaveTo(sImgPathResult);

    safeprintf(szErrorMsg, 512, "Comparison Image '%s' could not be read", sImgPathReference.GetData());
    return false;
  }

  if (ezImageConversion::Convert(imgExp, imgExpRGB, ezImageFormat::B8G8R8_UNORM).Failed())
  {
    imgRGB.SaveTo(sImgPathResult);

    safeprintf(szErrorMsg, 512, "Comparison Image '%s' could not be converted to BGR8", sImgPathReference.GetData());
    return false;
  }

  if (imgRGB.GetWidth() != imgExpRGB.GetWidth() || imgRGB.GetHeight() != imgExpRGB.GetHeight())
  {
    imgRGB.SaveTo(sImgPathResult);

    safeprintf(szErrorMsg, 512, "Comparison Image '%s' size (%ix%i) does not match captured image size (%ix%i)",
               sImgPathReference.GetData(), imgRGB.GetWidth(), imgRGB.GetHeight(), imgExpRGB.GetWidth(), imgExpRGB.GetHeight());
    return false;
  }

  ezImage imgDiff;
  ezImageUtils::ComputeImageDifferenceABS(imgExpRGB, imgRGB, imgDiff);

  const ezUInt32 uiMeanError = ezImageUtils::ComputeMeanSquareError(imgDiff, 32);

  if (uiMeanError > uiMaxError)
  {
    imgRGB.SaveTo(sImgPathResult);

    ezStringBuilder sImgDiffName;
    sImgDiffName.Format(":imgout/Images_Diff/{0}.tga", sImgName);

    imgDiff.SaveTo(sImgDiffName);

    safeprintf(szErrorMsg, 512, "Image Comparison Failed: Error of %u exceeds threshold of %u for image '%s'", uiMeanError, uiMaxError,
               sImgName.GetData());
    return false;
  }

  return true;
}

bool ezTestFramework::CompareImages(ezUInt32 uiImageNumber, ezUInt32 uiMaxError, char* szErrorMsg)
{
  ezStringBuilder sImgName;
  GenerateComparisonImageName(uiImageNumber, sImgName);

  ezImage img;
  if (GetTest(GetCurrentTestIndex())->m_pTest->GetImage(img).Failed())
  {
    safeprintf(szErrorMsg, 512, "Image '%s' could not be captured", sImgName.GetData());
    return false;
  }

  bool bImagesMatch = PerformImageComparison(sImgName, img, uiMaxError, szErrorMsg);

  if (m_ImageComparisonCallback)
  {
    m_ImageComparisonCallback(bImagesMatch);
  }

  return bImagesMatch;
}

void ezTestFramework::SetImageComparisonCallback(const ImageComparisonCallback& callback)
{
  m_ImageComparisonCallback = callback;
}

////////////////////////////////////////////////////////////////////////
// ezTestFramework static functions
////////////////////////////////////////////////////////////////////////

void ezTestFramework::Output(ezTestOutput::Enum Type, const char* szMsg, ...)
{
  va_list args;
  va_start(args, szMsg);

  OutputArgs(Type, szMsg, args);

  va_end(args);
}

void ezTestFramework::OutputArgs(ezTestOutput::Enum Type, const char* szMsg, va_list args)
{
  // format the output text
  char szBuffer[1024 * 10];
  ezStringUtils::vsnprintf(szBuffer, EZ_ARRAY_SIZE(szBuffer), szMsg, args);

  GetInstance()->OutputImpl(Type, szBuffer);
}

void ezTestFramework::Error(const char* szError, const char* szFile, ezInt32 iLine, const char* szFunction, const char* szMsg, ...)
{
  va_list args;
  va_start(args, szMsg);

  Error(szError, szFile, iLine, szFunction, szMsg, args);

  va_end(args);
}

void ezTestFramework::Error(const char* szError, const char* szFile, ezInt32 iLine, const char* szFunction, const char* szMsg, va_list args)
{
  // format the output text
  char szBuffer[1024 * 10];
  ezStringUtils::vsnprintf(szBuffer, EZ_ARRAY_SIZE(szBuffer), szMsg, args);

  GetInstance()->ErrorImpl(szError, szFile, iLine, szFunction, szBuffer);
}

void ezTestFramework::TestResult(ezInt32 iSubTestIndex, bool bSuccess, double fDuration)
{
  GetInstance()->TestResultImpl(iSubTestIndex, bSuccess, fDuration);
}

////////////////////////////////////////////////////////////////////////
// EZ_TEST_... macro functions
////////////////////////////////////////////////////////////////////////

#define OUTPUT_TEST_ERROR                                                                                                                  \
  {                                                                                                                                        \
    va_list args;                                                                                                                          \
    va_start(args, szMsg);                                                                                                                 \
    ezTestFramework::Error(szErrorText, szFile, iLine, szFunction, szMsg, args);                                                           \
    EZ_TEST_DEBUG_BREAK                                                                                                                    \
    va_end(args);                                                                                                                          \
    return EZ_FAILURE;                                                                                                                     \
  }

ezResult ezTestBool(bool bCondition, const char* szErrorText, const char* szFile, ezInt32 iLine, const char* szFunction, const char* szMsg,
                    ...)
{
  ezTestFramework::s_iAssertCounter++;

  if (!bCondition)
  {
    // if the test breaks here, go one up in the callstack to see where it exactly failed
    OUTPUT_TEST_ERROR
  }

  return EZ_SUCCESS;
}

ezResult ezTestDouble(double f1, double f2, double fEps, const char* szF1, const char* szF2, const char* szFile, ezInt32 iLine,
                      const char* szFunction, const char* szMsg, ...)
{
  ezTestFramework::s_iAssertCounter++;

  const double fD = f1 - f2;

  if (fD < -fEps || fD > +fEps)
  {
    char szErrorText[256];
    safeprintf(szErrorText, 256, "Failure: '%s' (%.8f) does not equal '%s' (%.8f) within an epsilon of %.8f", szF1, f1, szF2, f2, fEps);

    OUTPUT_TEST_ERROR
  }

  return EZ_SUCCESS;
}

ezResult ezTestInt(ezInt64 i1, ezInt64 i2, const char* szI1, const char* szI2, const char* szFile, ezInt32 iLine, const char* szFunction,
                   const char* szMsg, ...)
{
  ezTestFramework::s_iAssertCounter++;

  if (i1 != i2)
  {
    char szErrorText[256];
    safeprintf(szErrorText, 256, "Failure: '%s' (%i) does not equal '%s' (%i)", szI1, i1, szI2, i2);

    OUTPUT_TEST_ERROR
  }

  return EZ_SUCCESS;
}

ezResult ezTestString(std::string s1, std::string s2, const char* szString1, const char* szString2, const char* szFile, ezInt32 iLine,
                      const char* szFunction, const char* szMsg, ...)
{
  ezTestFramework::s_iAssertCounter++;

  if (s1 != s2)
  {
    char szErrorText[2048];
    safeprintf(szErrorText, 2048, "Failure: '%s' (%s) does not equal '%s' (%s)", szString1, s1.c_str(), szString2, s2.c_str());

    OUTPUT_TEST_ERROR
  }

  return EZ_SUCCESS;
}

ezResult ezTestVector(ezVec4d v1, ezVec4d v2, double fEps, const char* szCondition, const char* szFile, ezInt32 iLine,
                      const char* szFunction, const char* szMsg, ...)
{
  ezTestFramework::s_iAssertCounter++;

  char szErrorText[256];

  if (!ezMath::IsEqual(v1.x, v2.x, fEps))
  {
    safeprintf(szErrorText, 256, "Failure: '%s' - v1.x (%.8f) does not equal v2.x (%.8f) within an epsilon of %.8f", szCondition, v1.x,
               v2.x, fEps);

    OUTPUT_TEST_ERROR
  }

  if (!ezMath::IsEqual(v1.y, v2.y, fEps))
  {
    safeprintf(szErrorText, 256, "Failure: '%s' - v1.y (%.8f) does not equal v2.y (%.8f) within an epsilon of %.8f", szCondition, v1.y,
               v2.y, fEps);

    OUTPUT_TEST_ERROR
  }

  if (!ezMath::IsEqual(v1.z, v2.z, fEps))
  {
    safeprintf(szErrorText, 256, "Failure: '%s' - v1.z (%.8f) does not equal v2.z (%.8f) within an epsilon of %.8f", szCondition, v1.z,
               v2.z, fEps);

    OUTPUT_TEST_ERROR
  }

  if (!ezMath::IsEqual(v1.w, v2.w, fEps))
  {
    safeprintf(szErrorText, 256, "Failure: '%s' - v1.w (%.8f) does not equal v2.w (%.8f) within an epsilon of %.8f", szCondition, v1.w,
               v2.w, fEps);

    OUTPUT_TEST_ERROR
  }

  return EZ_SUCCESS;
}

ezResult ezTestFiles(const char* szFile1, const char* szFile2, const char* szFile, ezInt32 iLine, const char* szFunction, const char* szMsg,
                     ...)
{
  ezTestFramework::s_iAssertCounter++;

  char szErrorText[512];

  ezFileReader ReadFile1;
  ezFileReader ReadFile2;

  if (ReadFile1.Open(szFile1) == EZ_FAILURE)
  {
    safeprintf(szErrorText, 512, "Failure: File '%s' could not be read.", szFile1);

    OUTPUT_TEST_ERROR
  }
  else if (ReadFile2.Open(szFile2) == EZ_FAILURE)
  {
    safeprintf(szErrorText, 512, "Failure: File '%s' could not be read.", szFile2);

    OUTPUT_TEST_ERROR
  }

  else if (ReadFile1.GetFileSize() != ReadFile2.GetFileSize())
  {
    safeprintf(szErrorText, 512, "Failure: File sizes do not match: '%s' (%llu Bytes) and '%s' (%llu Bytes)", szFile1,
               ReadFile1.GetFileSize(), szFile2, ReadFile2.GetFileSize());

    OUTPUT_TEST_ERROR
  }
  else
  {
    while (true)
    {
      ezUInt8 uiTemp1[512];
      ezUInt8 uiTemp2[512];
      const ezUInt64 uiRead1 = ReadFile1.ReadBytes(uiTemp1, 512);
      const ezUInt64 uiRead2 = ReadFile2.ReadBytes(uiTemp2, 512);

      if (uiRead1 != uiRead2)
      {
        safeprintf(szErrorText, 512, "Failure: Files could not read same amount of data: '%s' and '%s'", szFile1, szFile2);

        OUTPUT_TEST_ERROR
      }
      else
      {
        if (uiRead1 == 0)
          break;

        if (memcmp(uiTemp1, uiTemp2, (size_t)uiRead1) != 0)
        {
          safeprintf(szErrorText, 512, "Failure: Files contents do not match: '%s' and '%s'", szFile1, szFile2);

          OUTPUT_TEST_ERROR
        }
      }
    }
  }

  return EZ_SUCCESS;
}

ezResult ezTestImage(ezUInt32 uiImageNumber, ezUInt32 uiMaxError, const char* szFile, ezInt32 iLine, const char* szFunction, const char* szMsg, ...)
{
  char szErrorText[512] = "";

  if (!ezTestFramework::GetInstance()->CompareImages(uiImageNumber, uiMaxError, szErrorText))
  {
    OUTPUT_TEST_ERROR
  }

  return EZ_SUCCESS;
}

EZ_STATICLINK_FILE(TestFramework, TestFramework_Framework_TestFramework);

