#include <RendererCorePCH.h>

#include <RendererCore/RendererCoreDLL.h>

#if EZ_ENABLED(EZ_EMBED_FONT_FILE)

// Font: https://fonts.google.com/specimen/Inconsolata
// License: Open Font License (http://scripts.sil.org/OFL_web)
// Used "Bitmap Font Builder" to create TGA file
// TGA is 256 * 128 pixels, only contains ASCII-7 characters, 1 channel 8 Bit and is RLE compressed
// Used Bin2C to convert file to C (http://tools.garry.tv/bin2c/)

extern ezUInt32 g_FontFileTGASize;
extern const ezUInt8 g_FontFileTGA[];

// clang-format off
ezUInt32 g_FontFileTGASize = 7892;
const ezUInt8 g_FontFileTGA[] =
{
  0,0,11,0,0,0,0,0,0,0,0,0,0,1,128,0,8,0,255,0,255,0,131,0,1,144,182,146,0,1,219,102,248,0,130,255,158,0,0,58,129,255,0,219,139,0,1,58,255,139,0,0,144,129,255,0,102,167,0,131,0,1,144,182,146,0,1,219,102,
  248,0,3,58,0,102,182,157,0,1,219,144,141,0,1,58,255,141,0,2,58,255,58,166,0,131,0,0,144,129,182,129,255,0,102,138,0,0,102,129,255,2,144,219,102,137,0,129,144,141,0,0,182,130,255,0,144,139,0,0,102,130,255,
  0,102,137,0,0,144,129,255,2,144,219,102,138,0,1,58,255,140,0,4,219,102,0,102,219,137,0,1,182,255,130,0,1,255,144,139,0,0,219,139,0,0,182,132,255,0,144,138,0,1,255,58,141,0,1,58,255,142,0,1,219,58,156,0,
  130,255,0,182,133,0,131,0,6,144,255,102,0,58,255,58,136,0,1,58,255,129,0,2,144,255,102,137,0,129,144,140,0,1,144,219,130,0,1,255,58,138,0,3,219,102,0,58,137,0,6,58,255,58,0,144,255,58,138,0,2,182,255,144,
  139,0,4,255,182,0,182,219,138,0,129,182,2,0,219,144,139,0,2,102,255,144,139,0,1,255,102,142,0,1,255,58,141,0,1,58,255,142,0,1,219,58,156,0,3,219,0,58,182,133,0,131,0,1,144,219,130,0,1,182,144,136,0,1,182,
  144,130,0,1,255,102,137,0,129,144,145,0,1,255,102,138,0,1,255,58,139,0,1,102,219,130,0,1,255,58,138,0,2,255,58,219,138,0,6,58,182,219,0,219,182,58,138,0,0,219,129,182,140,0,2,182,144,219,139,0,1,58,255,
  142,0,1,219,58,141,0,1,58,255,142,0,1,219,58,156,0,3,219,0,58,182,133,0,131,0,1,144,182,130,0,1,144,182,136,0,1,182,102,130,0,1,219,102,137,0,129,144,142,0,0,144,129,255,0,58,139,0,1,219,58,139,0,1,102,
  182,130,0,1,219,58,137,0,4,102,182,0,182,102,137,0,0,102,130,144,2,182,144,102,138,0,1,58,255,140,0,4,58,255,0,219,58,139,0,1,102,219,140,0,1,58,255,142,0,1,58,255,142,0,1,182,102,156,0,3,219,0,58,182,
  133,0,131,0,1,144,219,130,0,1,182,144,136,0,1,182,144,130,0,1,219,102,137,0,1,144,182,141,0,1,219,144,142,0,1,219,58,139,0,1,102,182,130,0,1,219,58,137,0,4,219,102,0,102,182,137,0,0,182,129,102,0,255,129,
  102,0,144,138,0,129,219,0,144,139,0,129,144,0,0,129,144,140,0,1,144,182,138,0,1,144,255,143,0,1,58,255,143,0,1,182,219,137,0,3,102,182,0,102,129,255,139,0,3,219,0,58,182,133,0,131,0,6,144,255,102,0,58,
  255,58,136,0,1,58,255,129,0,2,102,255,102,137,0,3,144,255,102,0,129,58,136,0,1,58,255,130,0,1,255,58,138,0,1,219,102,139,0,1,102,182,130,0,1,219,58,136,0,1,58,255,130,0,0,219,137,0,6,219,58,0,255,0,58,
  182,137,0,4,144,182,0,219,58,138,0,4,255,58,0,58,255,141,0,1,182,144,139,0,1,255,58,141,0,1,58,255,142,0,1,219,102,139,0,5,182,255,219,0,102,182,138,0,3,219,0,58,182,133,0,131,0,0,144,129,182,129,255,0,
  102,138,0,0,102,129,255,129,182,0,102,137,0,129,144,0,182,129,255,0,144,137,0,0,144,130,255,0,102,137,0,0,102,131,255,0,182,137,0,1,102,182,130,0,1,219,58,136,0,1,182,144,130,0,1,182,144,135,0,1,58,255,
  131,0,1,58,219,136,0,1,182,255,129,0,2,58,255,58,136,0,129,182,130,0,1,219,102,136,0,0,102,132,255,139,0,1,219,58,141,0,1,58,255,142,0,1,255,58,156,0,3,219,0,58,182,133,0,197,0,1,182,144,237,0,1,219,102,
  141,0,1,58,255,142,0,1,255,58,156,0,3,219,0,58,182,133,0,197,0,1,182,219,237,0,0,58,129,255,0,219,139,0,1,58,255,139,0,0,144,129,255,0,144,157,0,3,219,0,58,182,133,0,255,0,197,0,1,58,255,173,0,3,219,0,
  58,182,133,0,255,0,245,0,130,255,0,182,133,0,255,0,255,0,255,0,255,0,255,0,255,0,243,0,0,102,131,255,0,182,170,0,130,255,0,58,214,0,243,0,1,219,58,130,0,1,182,102,168,0,4,182,102,0,102,255,214,0,148,0,
  130,255,2,182,219,102,136,0,129,144,0,219,129,255,0,58,139,0,0,219,129,255,0,182,138,0,0,102,129,255,2,144,219,102,137,0,0,58,130,255,0,144,139,0,1,219,58,140,0,0,219,131,255,137,0,1,58,219,130,0,1,219,
  58,137,0,0,219,130,255,0,182,141,0,1,219,58,137,0,1,102,182,130,0,1,255,219,136,0,0,58,132,255,137,0,6,219,58,0,255,0,102,182,136,0,1,102,219,130,0,1,219,58,137,0,0,102,130,255,0,58,133,0,147,0,1,182,144,
  129,0,2,102,255,102,136,0,5,144,255,58,0,58,255,138,0,1,255,144,129,0,129,144,136,0,1,58,255,129,0,2,144,255,58,136,0,2,58,255,58,129,0,1,144,58,138,0,1,219,58,139,0,1,58,219,141,0,1,58,219,130,0,1,219,
  58,138,0,1,58,255,143,0,1,219,58,137,0,1,102,182,129,0,129,182,139,0,1,58,255,139,0,6,219,58,0,255,0,102,182,136,0,1,102,219,130,0,1,219,58,136,0,5,58,255,58,0,102,255,133,0,147,0,1,144,219,130,0,1,182,
  102,136,0,1,144,219,130,0,1,182,144,136,0,1,102,219,141,0,129,144,130,0,1,255,58,136,0,129,144,143,0,1,219,58,139,0,1,58,219,141,0,1,58,219,130,0,1,219,58,138,0,1,58,255,143,0,1,219,58,137,0,4,102,182,
  0,144,219,140,0,1,58,255,139,0,6,219,58,0,255,0,102,182,136,0,1,102,219,130,0,1,219,58,136,0,1,182,144,130,0,1,182,144,132,0,148,0,0,102,131,255,0,102,136,0,1,144,182,130,0,1,182,144,136,0,1,144,182,141,
  0,1,182,102,130,0,1,219,58,136,0,0,182,132,255,0,102,138,0,1,219,58,140,0,0,182,129,255,0,182,138,0,1,58,219,130,0,1,219,58,138,0,1,58,255,143,0,1,219,58,137,0,0,102,130,255,141,0,1,58,255,139,0,6,219,
  58,0,255,0,102,182,136,0,1,102,219,130,0,1,219,58,136,0,1,219,102,130,0,1,144,182,132,0,152,0,1,182,102,136,0,1,144,219,130,0,1,182,144,136,0,1,102,219,141,0,129,144,130,0,1,255,58,136,0,1,144,182,130,
  0,1,219,102,138,0,1,219,58,139,0,1,58,182,129,0,1,182,144,137,0,1,58,219,130,0,1,219,58,138,0,1,58,255,143,0,1,219,58,137,0,3,102,182,144,219,141,0,1,58,255,139,0,6,219,58,0,255,0,102,182,136,0,1,102,219,
  130,0,1,255,58,136,0,1,182,144,130,0,1,182,144,132,0,147,0,1,58,182,129,0,1,58,255,137,0,6,144,255,102,0,58,255,58,137,0,1,255,144,129,0,1,182,144,136,0,1,58,255,129,0,2,144,255,58,136,0,5,58,255,58,0,
  102,255,139,0,1,219,58,139,0,1,102,182,129,0,1,182,102,137,0,5,58,255,182,0,58,255,139,0,1,58,255,143,0,1,219,58,137,0,4,102,182,0,144,219,140,0,1,58,255,139,0,3,219,144,58,255,129,102,0,182,136,0,5,102,
  255,182,0,58,255,137,0,5,58,255,58,0,102,255,133,0,148,0,0,144,130,255,0,58,137,0,0,144,129,182,129,255,0,102,139,0,0,219,129,255,0,182,138,0,0,102,129,255,2,182,219,58,137,0,0,58,130,255,0,58,137,0,0,
  102,131,255,0,102,138,0,0,182,129,255,2,144,255,219,136,0,2,58,219,102,129,255,0,144,138,0,0,182,129,255,140,0,0,144,130,255,0,58,137,0,1,102,182,129,0,2,144,255,102,138,0,1,58,255,139,0,6,219,182,255,
  144,182,255,102,136,0,2,102,219,102,129,255,0,144,138,0,0,102,130,255,0,58,133,0,163,0,1,144,182,162,0,1,219,58,154,0,1,219,58,155,0,1,58,219,173,0,1,102,182,143,0,1,58,255,183,0,133,0,1,58,255,155,0,1,
  144,182,162,0,1,219,58,154,0,4,219,102,0,58,219,152,0,1,58,219,143,0,2,102,255,58,141,0,2,58,255,102,137,0,1,102,182,143,0,1,58,255,183,0,133,0,1,255,58,155,0,1,144,219,162,0,1,219,102,154,0,0,58,130,255,
  0,58,152,0,1,58,255,143,0,1,102,255,142,0,2,58,255,58,137,0,1,102,219,142,0,130,255,183,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,150,0,0,102,129,255,0,102,255,0,153,0,0,102,131,255,154,0,0,102,
  131,255,165,0,150,0,0,219,255,0,156,0,1,102,182,145,0,1,102,58,141,0,0,255,153,0,0,219,132,255,0,182,132,0,131,0,1,144,182,142,0,0,58,130,255,0,58,137,0,129,144,130,0,1,219,182,137,0,0,182,130,255,0,102,
  139,0,1,58,219,140,0,0,144,130,255,0,102,140,0,0,219,140,0,0,182,130,0,0,144,137,0,129,182,130,0,1,219,182,139,0,1,255,58,138,0,0,182,132,255,0,182,137,0,1,102,182,144,0,1,58,255,142,0,0,255,165,0,131,
  0,1,144,182,141,0,1,58,255,129,0,1,58,255,137,0,129,144,129,0,1,102,219,137,0,1,144,182,130,0,1,255,102,138,0,1,58,219,139,0,1,102,255,129,0,2,58,255,58,138,0,2,102,255,58,139,0,4,219,102,0,102,182,138,
  0,4,219,102,0,102,219,140,0,1,255,58,138,0,1,58,255,142,0,1,102,182,144,0,1,182,144,142,0,0,255,165,0,131,0,1,144,182,141,0,1,182,144,130,0,129,144,136,0,129,144,129,0,1,219,102,142,0,129,144,138,0,1,58,
  219,139,0,129,144,130,0,1,182,144,138,0,129,182,0,144,139,0,4,255,144,0,182,219,138,0,4,102,219,0,255,58,140,0,1,255,58,139,0,1,144,182,141,0,1,102,182,143,0,1,58,255,143,0,0,255,165,0,131,0,1,144,182,
  141,0,1,219,58,130,0,1,102,182,136,0,129,144,2,0,102,219,143,0,1,255,58,138,0,1,58,219,139,0,1,182,144,130,0,129,144,138,0,2,255,0,255,138,0,0,58,129,219,2,0,219,182,139,0,129,219,0,182,141,0,1,255,58,
  140,0,1,219,102,140,0,1,102,182,143,0,1,182,144,143,0,0,255,165,0,131,0,0,144,131,255,0,144,137,0,1,219,58,130,0,1,102,182,136,0,0,144,131,255,0,102,139,0,0,102,129,255,140,0,1,58,219,139,0,1,182,144,130,
  0,129,144,137,0,4,102,182,0,182,102,137,0,0,102,129,182,3,102,219,144,58,138,0,1,58,255,141,0,2,144,255,144,140,0,1,58,255,140,0,1,102,182,143,0,0,255,144,0,0,255,165,0,131,0,1,144,182,130,0,1,255,102,
  136,0,1,219,58,130,0,1,102,182,136,0,129,144,130,0,1,255,58,137,0,129,182,142,0,1,58,219,139,0,1,182,144,130,0,129,144,137,0,4,182,102,0,102,182,137,0,129,144,2,102,182,144,129,102,138,0,2,182,255,144,
  140,0,2,255,58,255,141,0,1,144,182,139,0,1,102,182,142,0,129,144,144,0,0,255,138,0,4,255,58,0,144,182,149,0,131,0,1,144,182,130,0,129,144,136,0,1,182,144,130,0,1,182,144,136,0,129,144,130,0,1,182,102,136,
  0,1,102,219,143,0,1,58,219,139,0,1,182,144,130,0,129,144,137,0,0,255,130,0,0,255,137,0,3,182,102,58,255,129,58,0,144,137,0,3,102,219,0,255,139,0,129,182,0,0,129,144,141,0,1,219,102,138,0,1,102,182,142,
  0,1,255,58,144,0,0,255,138,0,3,58,219,0,255,150,0,131,0,1,144,182,130,0,1,255,102,136,0,5,58,255,58,0,102,255,137,0,129,144,129,0,2,58,255,58,136,0,2,58,255,58,129,0,1,255,58,138,0,1,58,219,139,0,1,182,
  144,130,0,129,144,136,0,1,144,182,130,0,1,182,102,136,0,6,219,58,0,219,0,58,182,137,0,4,219,102,0,144,182,137,0,1,58,255,130,0,0,255,141,0,1,58,219,138,0,1,102,182,141,0,1,144,182,145,0,0,255,139,0,2,144,
  255,144,150,0,131,0,0,144,131,255,0,144,138,0,0,58,130,255,0,58,137,0,0,144,131,255,0,102,138,0,0,102,130,255,0,102,137,0,0,219,132,255,0,182,136,0,129,182,130,0,129,144,136,0,1,255,102,130,0,1,102,219,
  135,0,1,58,255,132,0,0,255,136,0,129,182,130,0,1,255,102,136,0,1,219,144,130,0,1,144,219,136,0,0,102,132,255,0,102,137,0,1,102,182,141,0,1,255,58,145,0,0,255,140,0,0,255,151,0,255,0,180,0,0,102,131,255,
  137,0,1,102,182,142,0,0,102,131,255,165,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,133,0,0,219,130,255,0,58,135,0,2,58,255,58,130,0,1,102,255,136,0,0,182,131,255,0,102,139,
  0,130,255,0,182,137,0,0,144,130,255,0,182,138,0,0,144,132,255,0,58,136,0,1,58,219,143,0,130,255,0,182,137,0,1,182,144,130,0,1,219,102,136,0,0,58,131,255,0,182,138,0,130,255,0,58,138,0,1,182,144,130,0,1,
  255,182,136,0,0,102,132,255,0,58,136,0,1,182,102,130,0,129,144,136,0,1,182,144,130,0,1,219,102,137,0,0,102,130,255,0,58,133,0,132,0,1,255,144,129,0,0,58,137,0,129,144,130,0,1,182,102,136,0,1,182,144,129,
  0,2,58,255,58,137,0,1,255,144,129,0,1,182,144,136,0,129,144,129,0,1,182,219,137,0,129,144,141,0,1,58,219,142,0,1,255,102,129,0,129,144,136,0,1,182,144,130,0,1,219,102,138,0,1,102,219,139,0,4,182,102,0,
  102,219,138,0,1,182,144,129,0,129,182,137,0,1,102,182,141,0,1,182,102,130,0,129,144,136,0,1,182,144,129,0,2,102,255,102,136,0,1,102,255,129,0,2,58,255,58,132,0,131,0,129,144,141,0,1,58,182,130,0,0,255,
  137,0,1,182,144,130,0,1,182,144,136,0,1,144,182,141,0,129,144,130,0,1,219,58,136,0,129,144,141,0,1,58,219,141,0,1,144,182,130,0,1,102,144,136,0,1,182,144,130,0,1,219,102,138,0,1,102,219,143,0,0,255,138,
  0,4,182,144,0,102,219,138,0,1,102,182,141,0,1,182,102,130,0,129,144,136,0,1,182,144,129,0,129,255,0,102,136,0,1,182,144,130,0,1,182,144,132,0,131,0,0,219,129,58,129,255,1,219,182,137,0,0,219,130,255,0,
  182,137,0,1,182,144,130,0,1,182,144,136,0,1,182,102,141,0,129,144,130,0,129,144,136,0,129,144,141,0,1,58,219,141,0,1,182,102,130,0,1,102,144,136,0,1,182,144,130,0,1,219,102,138,0,1,102,219,143,0,1,255,
  58,137,0,4,182,144,58,255,58,138,0,1,102,182,141,0,4,182,102,0,182,0,129,144,136,0,3,182,144,0,144,129,182,0,102,136,0,1,219,58,130,0,1,102,182,132,0,131,0,6,219,0,182,102,0,144,182,137,0,4,144,102,0,144,
  102,137,0,1,182,144,129,0,1,58,255,137,0,1,182,102,141,0,129,144,130,0,129,144,136,0,0,144,131,255,0,144,137,0,1,58,219,141,0,3,219,58,0,58,129,255,0,144,136,0,0,182,132,255,0,102,138,0,1,102,219,143,0,
  1,255,58,137,0,0,182,129,255,0,102,139,0,1,102,182,141,0,4,182,102,144,255,102,129,144,136,0,6,182,144,58,255,0,182,102,136,0,1,255,58,130,0,1,102,219,132,0,131,0,6,219,0,182,144,0,102,182,137,0,3,58,182,
  0,219,138,0,0,182,130,255,0,219,138,0,1,182,102,141,0,129,144,130,0,129,144,136,0,129,144,141,0,0,58,131,255,0,102,137,0,1,182,102,141,0,1,182,144,130,0,1,219,102,138,0,1,102,219,143,0,1,255,58,137,0,3,
  182,144,255,102,139,0,1,102,182,141,0,4,182,144,255,58,219,129,144,136,0,6,182,144,182,144,0,182,102,136,0,1,219,58,130,0,1,102,182,132,0,131,0,3,144,102,0,219,129,255,0,182,138,0,2,219,58,182,138,0,1,
  182,144,129,0,1,58,255,137,0,1,144,182,141,0,129,144,130,0,1,219,102,136,0,129,144,141,0,1,58,219,141,0,129,144,141,0,1,182,144,130,0,1,219,102,138,0,1,102,219,143,0,1,255,58,137,0,4,182,144,0,255,58,138,
  0,1,102,182,141,0,6,182,255,102,0,144,255,144,136,0,0,182,129,219,129,0,1,182,102,136,0,1,182,144,130,0,1,182,144,132,0,132,0,1,255,58,129,0,1,144,102,138,0,2,144,219,102,138,0,1,182,144,129,0,2,58,255,
  58,137,0,1,255,102,129,0,1,219,182,136,0,129,144,129,0,1,182,219,137,0,129,144,141,0,1,58,219,142,0,1,255,58,129,0,1,182,144,136,0,1,182,144,130,0,1,219,102,138,0,1,102,219,143,0,1,255,58,137,0,5,182,144,
  0,58,255,58,137,0,1,102,182,141,0,1,182,219,130,0,1,255,144,136,0,2,182,255,102,129,0,1,182,102,136,0,6,102,255,58,0,102,255,58,132,0,133,0,130,255,0,144,139,0,1,58,255,139,0,0,182,131,255,0,102,139,0,
  130,255,0,144,137,0,0,144,130,255,0,219,138,0,0,144,132,255,0,102,136,0,0,58,132,255,0,58,138,0,130,255,0,144,137,0,129,182,130,0,1,219,102,137,0,131,255,0,182,139,0,0,219,130,255,0,144,136,0,1,182,144,
  129,0,2,58,255,144,136,0,1,102,219,141,0,1,182,102,130,0,129,144,136,0,129,182,130,0,1,182,144,137,0,0,102,130,255,0,58,133,0,150,0,0,144,255,0,231,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,
  0,181,0,1,219,58,199,0,255,0,182,0,0,219,199,0,132,0,0,58,130,255,141,0,1,219,58,138,0,0,58,132,255,0,58,137,0,0,144,130,255,142,0,129,144,138,0,0,102,130,255,0,58,139,0,130,255,0,58,139,0,1,255,102,140,
  0,0,144,130,255,0,102,137,0,0,58,130,255,0,182,140,0,2,182,255,58,140,0,2,102,255,102,188,0,2,102,255,144,134,0,132,0,4,219,102,0,144,182,140,0,1,219,58,139,0,129,182,140,0,1,102,219,129,0,1,144,219,141,
  0,129,144,137,0,1,102,255,129,0,1,102,255,138,0,4,219,144,0,102,255,139,0,1,144,182,139,0,1,102,255,129,0,2,58,255,58,137,0,0,102,129,0,1,219,144,155,0,1,182,255,144,0,1,219,182,152,0,129,182,153,0,131,
  0,2,102,255,58,129,0,1,255,58,139,0,1,219,58,140,0,1,144,182,144,0,0,255,137,0,0,182,132,255,0,182,141,0,1,219,102,136,0,1,58,219,130,0,1,219,58,138,0,1,58,255,139,0,1,144,182,130,0,1,219,102,140,0,1,58,
  255,172,0,2,144,255,102,154,0,2,144,255,102,142,0,0,255,135,0,131,0,2,144,182,219,129,0,1,219,102,139,0,1,219,58,141,0,1,144,182,143,0,0,255,137,0,1,58,255,129,0,129,144,142,0,1,219,102,136,0,1,102,182,
  130,0,1,219,58,139,0,1,219,102,139,0,0,255,129,0,1,58,255,142,0,1,255,58,169,0,2,58,255,182,158,0,1,219,255,141,0,1,219,58,134,0,131,0,6,144,182,0,255,0,219,102,139,0,1,219,58,142,0,1,182,144,141,0,1,144,
  182,138,0,2,144,182,0,129,144,138,0,0,255,129,0,1,102,255,137,0,5,102,255,102,0,102,255,140,0,1,144,182,140,0,130,255,139,0,0,102,130,255,1,219,58,168,0,129,219,141,0,0,182,132,255,0,144,141,0,1,255,182,
  139,0,1,144,182,134,0,131,0,3,144,182,0,58,129,219,0,102,139,0,1,219,58,143,0,0,255,139,0,2,182,255,144,140,0,1,219,102,129,144,138,0,131,255,0,58,137,0,2,58,219,182,129,255,0,58,140,0,1,58,255,139,0,4,
  144,219,0,182,144,137,0,1,58,255,130,0,1,255,58,138,0,2,182,255,58,140,0,2,182,255,58,138,0,2,58,255,219,160,0,129,255,141,0,1,182,144,133,0,131,0,1,102,219,129,0,2,58,255,58,139,0,1,219,58,143,0,1,219,
  58,140,0,1,144,182,140,0,0,255,129,144,138,0,0,219,142,0,0,255,145,0,1,182,102,138,0,0,255,130,0,0,255,137,0,1,102,182,130,0,1,219,58,170,0,2,58,255,182,138,0,0,182,132,255,0,144,138,0,1,219,255,144,0,
  0,255,133,0,132,0,4,219,102,0,144,182,138,0,3,255,144,219,58,138,0,1,144,255,129,0,1,58,255,138,0,0,182,129,0,1,102,219,140,0,2,102,255,144,138,0,1,219,58,141,0,129,182,129,0,0,102,141,0,1,102,219,138,
  0,4,219,102,0,102,219,137,0,5,58,255,58,0,102,219,173,0,2,102,255,144,152,0,2,182,255,58,145,0,1,219,58,132,0,132,0,0,58,130,255,140,0,2,144,255,58,139,0,0,102,130,255,0,102,138,0,0,102,130,255,0,58,141,
  0,1,182,144,138,0,0,219,131,255,139,0,0,182,130,255,137,0,0,58,132,255,0,58,137,0,0,58,130,255,0,58,138,0,0,102,130,255,218,0,1,102,219,129,0,1,102,255,133,0,255,0,244,0,0,102,130,255,0,58,133,0,255,0,
  255,0,255,0,255,0,255,0,255,0,255,0,136,0,0,102,138,0,0,58,233,0,255,0,134,0,2,58,255,182,138,0,2,144,255,102,173,0,1,219,58,183,0,198,0,0,219,190,0,1,255,102,141,0,1,255,102,173,0,0,219,171,0,129,58,137,
  0,149,0,2,182,255,58,155,0,3,219,58,102,182,139,0,0,182,130,255,0,144,137,0,1,182,144,129,0,2,219,255,102,137,0,130,255,2,58,144,219,154,0,1,182,144,142,0,1,58,255,172,0,2,102,255,102,156,0,2,182,255,58,
  138,0,1,58,255,137,0,149,0,1,144,255,156,0,0,182,129,58,0,219,138,0,6,144,182,0,219,0,219,102,137,0,1,219,0,129,144,1,0,219,136,0,129,182,129,0,129,255,0,58,153,0,1,58,255,144,0,1,182,102,171,0,1,182,255,
  172,0,1,182,144,136,0,180,0,3,144,102,0,219,141,0,3,219,0,102,144,137,0,5,58,182,102,144,0,219,136,0,1,219,102,129,0,129,255,0,58,153,0,1,102,182,144,0,1,144,182,138,0,4,255,58,0,102,219,140,0,0,255,188,
  0,1,58,255,136,0,149,0,1,58,182,155,0,133,255,0,144,139,0,3,219,0,219,102,138,0,4,182,58,219,255,102,136,0,6,102,219,0,182,144,58,219,153,0,129,144,144,0,1,102,219,138,0,3,58,219,0,255,141,0,0,255,189,
  0,1,182,144,135,0,149,0,1,58,182,156,0,4,102,144,0,219,58,139,0,0,102,129,255,0,102,140,0,0,219,140,0,2,144,255,182,156,0,1,144,182,144,0,1,102,182,139,0,2,102,255,58,141,0,0,255,155,0,0,102,132,255,0,
  58,154,0,1,58,219,135,0,149,0,1,102,219,156,0,4,58,182,0,182,102,138,0,2,182,255,219,139,0,4,102,255,219,144,102,139,0,3,102,219,182,144,155,0,1,102,219,144,0,129,144,137,0,3,182,255,219,182,129,255,0,
  144,136,0,0,182,132,255,0,144,187,0,1,182,102,134,0,149,0,1,102,219,140,0,3,58,182,0,219,138,0,0,219,132,255,0,219,136,0,3,58,219,0,219,139,0,1,219,0,129,144,0,219,139,0,3,219,58,0,255,141,0,0,219,141,
  0,1,255,102,143,0,1,255,58,137,0,0,58,129,0,0,219,142,0,0,255,190,0,1,102,219,134,0,149,0,1,102,255,140,0,3,58,219,0,255,140,0,3,255,0,102,144,138,0,5,255,0,219,0,182,102,136,0,2,219,0,144,129,102,0,144,
  138,0,4,255,58,0,255,58,139,0,1,58,255,141,0,1,102,255,142,0,129,182,140,0,1,58,255,142,0,0,255,191,0,1,219,102,133,0,149,0,1,144,255,140,0,4,102,219,0,255,58,139,0,3,219,58,102,182,138,0,0,58,130,255,
  0,144,137,0,2,102,255,219,129,0,1,219,102,137,0,0,102,129,255,0,144,140,0,1,58,255,142,0,1,144,255,140,0,1,182,219,223,0,1,102,219,133,0,149,0,1,102,255,140,0,4,102,219,0,255,58,156,0,1,219,58,172,0,1,
  58,255,143,0,1,102,219,138,0,129,144,225,0,1,219,58,132,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,255,0,133,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,
  139,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,197,0,133,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,
  0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,197,0,133,0,0,219,129,0,0,
  219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,
  0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,197,0,133,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,
  129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,197,0,133,0,0,219,129,0,0,219,139,0,0,219,129,
  0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,
  0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,197,0,133,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,
  219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,197,0,133,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,
  129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,
  139,0,0,219,129,0,0,219,197,0,133,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,
  0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,197,0,133,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,
  219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,
  0,219,197,0,133,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,
  139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,197,0,133,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,
  0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,197,0,133,0,131,
  255,139,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,197,0,255,0,255,0,255,0,255,0,255,0,255,0,255,
  0,255,0,149,0,131,255,155,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,171,0,131,255,139,0,0,144,129,255,156,0,131,255,139,0,131,255,133,0,149,0,0,219,129,0,0,219,155,
  0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,171,0,0,219,129,0,0,219,136,0,3,144,58,0,144,129,255,129,0,1,
  144,58,152,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,133,0,149,0,0,219,129,0,0,219,155,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,
  219,139,0,0,219,129,0,0,219,171,0,0,219,129,0,0,219,136,0,3,144,255,58,144,129,255,3,0,144,255,58,152,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,133,0,149,0,0,219,129,0,0,219,155,0,0,219,129,0,0,219,139,
  0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,171,0,0,219,129,0,0,219,136,0,0,144,129,255,0,182,129,255,0,144,129,255,0,58,152,0,0,
  219,129,0,0,219,139,0,0,219,129,0,0,219,133,0,149,0,0,219,129,0,0,219,155,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,
  129,0,0,219,171,0,0,219,129,0,0,219,136,0,0,102,135,255,153,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,133,0,149,0,0,219,129,0,0,219,155,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,
  219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,171,0,0,219,129,0,0,219,137,0,0,102,133,255,154,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,133,0,149,0,0,219,129,0,0,219,155,
  0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,171,0,0,219,129,0,0,219,138,0,0,102,131,255,155,0,0,219,129,0,
  0,219,139,0,0,219,129,0,0,219,133,0,149,0,0,219,129,0,0,219,155,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,
  171,0,0,219,129,0,0,219,139,0,0,102,129,255,156,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,133,0,149,0,0,219,129,0,0,219,155,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,
  219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,171,0,0,219,129,0,0,219,140,0,0,102,157,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,133,0,149,0,0,219,129,0,0,219,155,0,0,219,129,0,0,219,
  139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,171,0,0,219,129,0,0,219,171,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,133,0,149,
  0,0,219,129,0,0,219,155,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,139,0,0,219,129,0,0,219,171,0,0,219,129,0,0,219,171,0,0,219,129,
  0,0,219,139,0,0,219,129,0,0,219,133,0,149,0,131,255,155,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,139,0,131,255,171,0,131,255,171,0,131,255,139,0,131,255,133,0,255,0,255,0,255,0,
  255,0,0,0,0,0,0,0,0,0,84,82,85,69,86,73,83,73,79,78,45,88,70,73,76,69,46,0,0
};

#endif



EZ_STATICLINK_FILE(RendererCore, RendererCore_Debug_Implementation_Inconsolata);

