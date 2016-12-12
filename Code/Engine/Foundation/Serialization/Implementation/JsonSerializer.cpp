#include <Foundation/PCH.h>
#include <Foundation/Serialization/JsonSerializer.h>
#include <Foundation/Serialization/AbstractObjectGraph.h>
#include <Foundation/Serialization/GraphVersioning.h>
#include <Foundation/IO/Stream.h>
#include <Foundation/IO/ExtendedJSONWriter.h>
#include <Foundation/IO/ExtendedJSONReader.h>
#include <Foundation/Logging/Log.h>

static void WriteGraph(ezExtendedJSONWriter &writer, const ezAbstractObjectGraph* pGraph, const char* szName)
{
  ezMap<const char*, const ezVariant*, CompareConstChar> SortedProperties;

  writer.BeginArray(szName);

  const auto& Nodes = pGraph->GetAllNodes();
  for (auto itNode = Nodes.GetIterator(); itNode.IsValid(); ++itNode)
  {
    writer.BeginObject();
    {
      const auto& node = *itNode.Value();

      writer.AddVariableUuid("#", node.GetGuid());
      writer.AddVariableString("t", node.GetType());
      writer.AddVariableUInt32("v", node.GetTypeVersion());

      if (node.GetNodeName() != nullptr)
        writer.AddVariableString("n", node.GetNodeName());

      writer.BeginObject("p");
      {
        for (const auto& prop : node.GetProperties())
          SortedProperties[prop.m_szPropertyName] = &prop.m_Value;

        for (auto it = SortedProperties.GetIterator(); it.IsValid(); ++it)
        {
          writer.AddVariableVariant(it.Key(), *it.Value());
        }

        SortedProperties.Clear();
      }
      writer.EndObject();
    }
    writer.EndObject();
  }

  writer.EndArray();
}

void ezAbstractGraphJsonSerializer::Write(ezStreamWriter& stream, const ezAbstractObjectGraph* pGraph, const ezAbstractObjectGraph* pTypesGraph, ezStandardJSONWriter::WhitespaceMode mode)
{

  ezExtendedJSONWriter writer;
  writer.SetOutputStream(&stream);
  writer.SetWhitespaceMode(mode);

  writer.BeginObject();
  {
    WriteGraph(writer, pGraph, "Objects");
    if (pTypesGraph)
    {
      WriteGraph(writer, pTypesGraph, "Types");
    }
  }
  writer.EndObject();
}



static void ReadGraph(ezExtendedJSONReader &reader, ezAbstractObjectGraph* pGraph, const char* szName)
{
  ezVariant* pObjects;
  if (!reader.GetTopLevelObject().TryGetValue(szName, pObjects))
  {
    EZ_REPORT_FAILURE("JSON file does not contain an '%s' node at root level", szName);
    return;
  }

  EZ_ASSERT_DEV(pObjects->IsA<ezVariantArray>(), "'{0}' node is not of type array", szName);

  const ezVariantArray& ObjArray = pObjects->Get<ezVariantArray>();

  for (const auto& object : ObjArray)
  {
    EZ_ASSERT_DEV(object.IsA<ezVariantDictionary>(), "'{0}' array contains elements that are not dictionaries", szName);

    const auto& ObjDict = object.Get<ezVariantDictionary>();

    ezVariant* pGuid = nullptr;
    ezVariant* pType = nullptr;
    ezVariant* pTypeVersion = nullptr;
    ezVariant* pProp = nullptr;
    ezVariant* pNodeName = nullptr;
    ObjDict.TryGetValue("#", pGuid);
    ObjDict.TryGetValue("t", pType);
    ObjDict.TryGetValue("v", pTypeVersion);
    ObjDict.TryGetValue("p", pProp);
    ObjDict.TryGetValue("n", pNodeName);

    if (pGuid == nullptr || pType == nullptr || pProp == nullptr ||
      !pGuid->IsA<ezUuid>() || !pType->IsA<ezString>() || !pProp->IsA<ezVariantDictionary>())
    {
      EZ_REPORT_FAILURE("'%s' array contains invalid elements", szName);
      continue;
    }

    const char* szNodeName = nullptr;
    if (pNodeName != nullptr && pNodeName->IsA<ezString>())
      szNodeName = pNodeName->Get<ezString>();

    ezUInt32 uiTypeVersion = 0;
    if (pTypeVersion && pTypeVersion->CanConvertTo<ezUInt32>())
      uiTypeVersion = pTypeVersion->ConvertTo<ezUInt32>();

    auto* pNode = pGraph->AddNode(pGuid->Get<ezUuid>(), pType->Get<ezString>(), uiTypeVersion, szNodeName);

    const ezVariantDictionary& Properties = pProp->Get<ezVariantDictionary>();
    for (auto propIt = Properties.GetIterator(); propIt.IsValid(); ++propIt)
    {
      pNode->AddProperty(propIt.Key(), propIt.Value());
    }
  }
}

ezResult ezAbstractGraphJsonSerializer::Read(ezStreamReader& stream, ezAbstractObjectGraph* pGraph, ezAbstractObjectGraph* pTypesGraph, bool bApplyPatches)
{
  ezExtendedJSONReader reader;
  reader.SetLogInterface(ezGlobalLog::GetOrCreateInstance());
  if (reader.Parse(stream).Failed())
  {
    EZ_REPORT_FAILURE("Failed to parse JSON graph");
    return EZ_FAILURE;
  }

  ReadGraph(reader, pGraph, "Objects");
  if (pTypesGraph && reader.GetTopLevelObject().Contains("Types"))
  {
    ReadGraph(reader, pTypesGraph, "Types");
  }

  if (bApplyPatches)
    ezGraphVersioning::GetSingleton()->PatchGraph(pGraph);
  return EZ_SUCCESS;
}

EZ_STATICLINK_FILE(Foundation, Foundation_Serialization_Implementation_JsonSerializer);
