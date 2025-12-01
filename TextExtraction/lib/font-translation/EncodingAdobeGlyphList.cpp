#include "Encoding.h"
#include "EncodingAdobeGlyphList.h"

namespace {

struct GlyphListEntry {
    const char* name;
    const unsigned long* codepoints;
    size_t count;
};

// Codepoint arrays
static const unsigned long cp_1501[] = {0x05D3, 0x05B2};
static const unsigned long cp_1502[] = {0x05D3, 0x05B2};
static const unsigned long cp_1503[] = {0x05D3, 0x05B1};
static const unsigned long cp_1504[] = {0x05D3, 0x05B1};
static const unsigned long cp_1506[] = {0x05D3, 0x05B4};
static const unsigned long cp_1507[] = {0x05D3, 0x05B4};
static const unsigned long cp_1508[] = {0x05D3, 0x05B9};
static const unsigned long cp_1509[] = {0x05D3, 0x05B9};
static const unsigned long cp_1510[] = {0x05D3, 0x05B7};
static const unsigned long cp_1511[] = {0x05D3, 0x05B7};
static const unsigned long cp_1512[] = {0x05D3, 0x05B8};
static const unsigned long cp_1513[] = {0x05D3, 0x05B8};
static const unsigned long cp_1514[] = {0x05D3, 0x05BB};
static const unsigned long cp_1515[] = {0x05D3, 0x05BB};
static const unsigned long cp_1516[] = {0x05D3, 0x05B6};
static const unsigned long cp_1517[] = {0x05D3, 0x05B6};
static const unsigned long cp_1518[] = {0x05D3, 0x05B0};
static const unsigned long cp_1519[] = {0x05D3, 0x05B0};
static const unsigned long cp_1520[] = {0x05D3, 0x05B5};
static const unsigned long cp_1521[] = {0x05D3, 0x05B5};
static const unsigned long cp_1838[] = {0x05DA, 0x05B8};
static const unsigned long cp_1839[] = {0x05DA, 0x05B8};
static const unsigned long cp_1840[] = {0x05DA, 0x05B0};
static const unsigned long cp_1841[] = {0x05DA, 0x05B0};
static const unsigned long cp_2030[] = {0x0621, 0x064F};
static const unsigned long cp_2031[] = {0x0621, 0x064C};
static const unsigned long cp_2032[] = {0x0621, 0x064E};
static const unsigned long cp_2033[] = {0x0621, 0x064B};
static const unsigned long cp_2035[] = {0x0621, 0x0650};
static const unsigned long cp_2036[] = {0x0621, 0x064D};
static const unsigned long cp_2037[] = {0x0621, 0x0652};
static const unsigned long cp_2469[] = {0x05DC, 0x05B9};
static const unsigned long cp_2470[] = {0x05DC, 0x05B9, 0x05BC};
static const unsigned long cp_2471[] = {0x05DC, 0x05B9, 0x05BC};
static const unsigned long cp_2472[] = {0x05DC, 0x05B9};
static const unsigned long cp_2482[] = {0xFEDF, 0xFEE4, 0xFEA0};
static const unsigned long cp_2483[] = {0xFEDF, 0xFEE4, 0xFEA8};
static const unsigned long cp_2780[] = {0xFEE7, 0xFEEC};
static const unsigned long cp_3152[] = {0x05E7, 0x05B2};
static const unsigned long cp_3153[] = {0x05E7, 0x05B2};
static const unsigned long cp_3154[] = {0x05E7, 0x05B1};
static const unsigned long cp_3155[] = {0x05E7, 0x05B1};
static const unsigned long cp_3157[] = {0x05E7, 0x05B4};
static const unsigned long cp_3158[] = {0x05E7, 0x05B4};
static const unsigned long cp_3159[] = {0x05E7, 0x05B9};
static const unsigned long cp_3160[] = {0x05E7, 0x05B9};
static const unsigned long cp_3161[] = {0x05E7, 0x05B7};
static const unsigned long cp_3162[] = {0x05E7, 0x05B7};
static const unsigned long cp_3163[] = {0x05E7, 0x05B8};
static const unsigned long cp_3164[] = {0x05E7, 0x05B8};
static const unsigned long cp_3165[] = {0x05E7, 0x05BB};
static const unsigned long cp_3166[] = {0x05E7, 0x05BB};
static const unsigned long cp_3167[] = {0x05E7, 0x05B6};
static const unsigned long cp_3168[] = {0x05E7, 0x05B6};
static const unsigned long cp_3169[] = {0x05E7, 0x05B0};
static const unsigned long cp_3170[] = {0x05E7, 0x05B0};
static const unsigned long cp_3171[] = {0x05E7, 0x05B5};
static const unsigned long cp_3172[] = {0x05E7, 0x05B5};
static const unsigned long cp_3246[] = {0x0631, 0xFEF3, 0xFE8E, 0x0644};
static const unsigned long cp_3251[] = {0x05E8, 0x05B2};
static const unsigned long cp_3252[] = {0x05E8, 0x05B2};
static const unsigned long cp_3253[] = {0x05E8, 0x05B1};
static const unsigned long cp_3254[] = {0x05E8, 0x05B1};
static const unsigned long cp_3256[] = {0x05E8, 0x05B4};
static const unsigned long cp_3257[] = {0x05E8, 0x05B4};
static const unsigned long cp_3258[] = {0x05E8, 0x05B9};
static const unsigned long cp_3259[] = {0x05E8, 0x05B9};
static const unsigned long cp_3260[] = {0x05E8, 0x05B7};
static const unsigned long cp_3261[] = {0x05E8, 0x05B7};
static const unsigned long cp_3262[] = {0x05E8, 0x05B8};
static const unsigned long cp_3263[] = {0x05E8, 0x05B8};
static const unsigned long cp_3264[] = {0x05E8, 0x05BB};
static const unsigned long cp_3265[] = {0x05E8, 0x05BB};
static const unsigned long cp_3266[] = {0x05E8, 0x05B6};
static const unsigned long cp_3267[] = {0x05E8, 0x05B6};
static const unsigned long cp_3268[] = {0x05E8, 0x05B0};
static const unsigned long cp_3269[] = {0x05E8, 0x05B0};
static const unsigned long cp_3270[] = {0x05E8, 0x05B5};
static const unsigned long cp_3271[] = {0x05E8, 0x05B5};
static const unsigned long cp_3470[] = {0x0651, 0x064B};
static const unsigned long cp_3667[] = {0xFB7C, 0xFEE4};

static const unsigned long cp_single_0[] = {0x0041};
static const unsigned long cp_single_1[] = {0x00c6};
static const unsigned long cp_single_2[] = {0x01fc};
static const unsigned long cp_single_3[] = {0x01e2};
static const unsigned long cp_single_4[] = {0xf7e6};
static const unsigned long cp_single_5[] = {0x00c1};
static const unsigned long cp_single_6[] = {0xf7e1};
static const unsigned long cp_single_7[] = {0x0102};
static const unsigned long cp_single_8[] = {0x1eae};
static const unsigned long cp_single_9[] = {0x04d0};
static const unsigned long cp_single_10[] = {0x1eb6};
static const unsigned long cp_single_11[] = {0x1eb0};
static const unsigned long cp_single_12[] = {0x1eb2};
static const unsigned long cp_single_13[] = {0x1eb4};
static const unsigned long cp_single_14[] = {0x01cd};
static const unsigned long cp_single_15[] = {0x24b6};
static const unsigned long cp_single_16[] = {0x00c2};
static const unsigned long cp_single_17[] = {0x1ea4};
static const unsigned long cp_single_18[] = {0x1eac};
static const unsigned long cp_single_19[] = {0x1ea6};
static const unsigned long cp_single_20[] = {0x1ea8};
static const unsigned long cp_single_21[] = {0xf7e2};
static const unsigned long cp_single_22[] = {0x1eaa};
static const unsigned long cp_single_23[] = {0xf6c9};
static const unsigned long cp_single_24[] = {0xf7b4};
static const unsigned long cp_single_25[] = {0x0410};
static const unsigned long cp_single_26[] = {0x0200};
static const unsigned long cp_single_27[] = {0x00c4};
static const unsigned long cp_single_28[] = {0x04d2};
static const unsigned long cp_single_29[] = {0x01de};
static const unsigned long cp_single_30[] = {0xf7e4};
static const unsigned long cp_single_31[] = {0x1ea0};
static const unsigned long cp_single_32[] = {0x01e0};
static const unsigned long cp_single_33[] = {0x00c0};
static const unsigned long cp_single_34[] = {0xf7e0};
static const unsigned long cp_single_35[] = {0x1ea2};
static const unsigned long cp_single_36[] = {0x04d4};
static const unsigned long cp_single_37[] = {0x0202};
static const unsigned long cp_single_38[] = {0x0391};
static const unsigned long cp_single_39[] = {0x0386};
static const unsigned long cp_single_40[] = {0x0100};
static const unsigned long cp_single_41[] = {0xff21};
static const unsigned long cp_single_42[] = {0x0104};
static const unsigned long cp_single_43[] = {0x00c5};
static const unsigned long cp_single_44[] = {0x01fa};
static const unsigned long cp_single_45[] = {0x1e00};
static const unsigned long cp_single_46[] = {0xf7e5};
static const unsigned long cp_single_47[] = {0xf761};
static const unsigned long cp_single_48[] = {0x00c3};
static const unsigned long cp_single_49[] = {0xf7e3};
static const unsigned long cp_single_50[] = {0x0531};
static const unsigned long cp_single_51[] = {0x0042};
static const unsigned long cp_single_52[] = {0x24b7};
static const unsigned long cp_single_53[] = {0x1e02};
static const unsigned long cp_single_54[] = {0x1e04};
static const unsigned long cp_single_55[] = {0x0411};
static const unsigned long cp_single_56[] = {0x0532};
static const unsigned long cp_single_57[] = {0x0392};
static const unsigned long cp_single_58[] = {0x0181};
static const unsigned long cp_single_59[] = {0x1e06};
static const unsigned long cp_single_60[] = {0xff22};
static const unsigned long cp_single_61[] = {0xf6f4};
static const unsigned long cp_single_62[] = {0xf762};
static const unsigned long cp_single_63[] = {0x0182};
static const unsigned long cp_single_64[] = {0x0043};
static const unsigned long cp_single_65[] = {0x053e};
static const unsigned long cp_single_66[] = {0x0106};
static const unsigned long cp_single_67[] = {0xf6ca};
static const unsigned long cp_single_68[] = {0xf6f5};
static const unsigned long cp_single_69[] = {0x010c};
static const unsigned long cp_single_70[] = {0x00c7};
static const unsigned long cp_single_71[] = {0x1e08};
static const unsigned long cp_single_72[] = {0xf7e7};
static const unsigned long cp_single_73[] = {0x24b8};
static const unsigned long cp_single_74[] = {0x0108};
static const unsigned long cp_single_75[] = {0x010a};
static const unsigned long cp_single_76[] = {0x010a};
static const unsigned long cp_single_77[] = {0xf7b8};
static const unsigned long cp_single_78[] = {0x0549};
static const unsigned long cp_single_79[] = {0x04bc};
static const unsigned long cp_single_80[] = {0x0427};
static const unsigned long cp_single_81[] = {0x04be};
static const unsigned long cp_single_82[] = {0x04b6};
static const unsigned long cp_single_83[] = {0x04f4};
static const unsigned long cp_single_84[] = {0x0543};
static const unsigned long cp_single_85[] = {0x04cb};
static const unsigned long cp_single_86[] = {0x04b8};
static const unsigned long cp_single_87[] = {0x03a7};
static const unsigned long cp_single_88[] = {0x0187};
static const unsigned long cp_single_89[] = {0xf6f6};
static const unsigned long cp_single_90[] = {0xff23};
static const unsigned long cp_single_91[] = {0x0551};
static const unsigned long cp_single_92[] = {0xf763};
static const unsigned long cp_single_93[] = {0x0044};
static const unsigned long cp_single_94[] = {0x01f1};
static const unsigned long cp_single_95[] = {0x01c4};
static const unsigned long cp_single_96[] = {0x0534};
static const unsigned long cp_single_97[] = {0x0189};
static const unsigned long cp_single_98[] = {0x010e};
static const unsigned long cp_single_99[] = {0x1e10};
static const unsigned long cp_single_100[] = {0x24b9};
static const unsigned long cp_single_101[] = {0x1e12};
static const unsigned long cp_single_102[] = {0x0110};
static const unsigned long cp_single_103[] = {0x1e0a};
static const unsigned long cp_single_104[] = {0x1e0c};
static const unsigned long cp_single_105[] = {0x0414};
static const unsigned long cp_single_106[] = {0x03ee};
static const unsigned long cp_single_107[] = {0x2206};
static const unsigned long cp_single_108[] = {0x0394};
static const unsigned long cp_single_109[] = {0x018a};
static const unsigned long cp_single_110[] = {0xf6cb};
static const unsigned long cp_single_111[] = {0xf6cc};
static const unsigned long cp_single_112[] = {0xf6cd};
static const unsigned long cp_single_113[] = {0xf7a8};
static const unsigned long cp_single_114[] = {0x03dc};
static const unsigned long cp_single_115[] = {0x0402};
static const unsigned long cp_single_116[] = {0x1e0e};
static const unsigned long cp_single_117[] = {0xff24};
static const unsigned long cp_single_118[] = {0xf6f7};
static const unsigned long cp_single_119[] = {0x0110};
static const unsigned long cp_single_120[] = {0xf764};
static const unsigned long cp_single_121[] = {0x018b};
static const unsigned long cp_single_122[] = {0x01f2};
static const unsigned long cp_single_123[] = {0x01c5};
static const unsigned long cp_single_124[] = {0x04e0};
static const unsigned long cp_single_125[] = {0x0405};
static const unsigned long cp_single_126[] = {0x040f};
static const unsigned long cp_single_127[] = {0x0045};
static const unsigned long cp_single_128[] = {0x00c9};
static const unsigned long cp_single_129[] = {0xf7e9};
static const unsigned long cp_single_130[] = {0x0114};
static const unsigned long cp_single_131[] = {0x011a};
static const unsigned long cp_single_132[] = {0x1e1c};
static const unsigned long cp_single_133[] = {0x0535};
static const unsigned long cp_single_134[] = {0x24ba};
static const unsigned long cp_single_135[] = {0x00ca};
static const unsigned long cp_single_136[] = {0x1ebe};
static const unsigned long cp_single_137[] = {0x1e18};
static const unsigned long cp_single_138[] = {0x1ec6};
static const unsigned long cp_single_139[] = {0x1ec0};
static const unsigned long cp_single_140[] = {0x1ec2};
static const unsigned long cp_single_141[] = {0xf7ea};
static const unsigned long cp_single_142[] = {0x1ec4};
static const unsigned long cp_single_143[] = {0x0404};
static const unsigned long cp_single_144[] = {0x0204};
static const unsigned long cp_single_145[] = {0x00cb};
static const unsigned long cp_single_146[] = {0xf7eb};
static const unsigned long cp_single_147[] = {0x0116};
static const unsigned long cp_single_148[] = {0x0116};
static const unsigned long cp_single_149[] = {0x1eb8};
static const unsigned long cp_single_150[] = {0x0424};
static const unsigned long cp_single_151[] = {0x00c8};
static const unsigned long cp_single_152[] = {0xf7e8};
static const unsigned long cp_single_153[] = {0x0537};
static const unsigned long cp_single_154[] = {0x1eba};
static const unsigned long cp_single_155[] = {0x2167};
static const unsigned long cp_single_156[] = {0x0206};
static const unsigned long cp_single_157[] = {0x0464};
static const unsigned long cp_single_158[] = {0x041b};
static const unsigned long cp_single_159[] = {0x216a};
static const unsigned long cp_single_160[] = {0x0112};
static const unsigned long cp_single_161[] = {0x1e16};
static const unsigned long cp_single_162[] = {0x1e14};
static const unsigned long cp_single_163[] = {0x041c};
static const unsigned long cp_single_164[] = {0xff25};
static const unsigned long cp_single_165[] = {0x041d};
static const unsigned long cp_single_166[] = {0x04a2};
static const unsigned long cp_single_167[] = {0x014a};
static const unsigned long cp_single_168[] = {0x04a4};
static const unsigned long cp_single_169[] = {0x04c7};
static const unsigned long cp_single_170[] = {0x0118};
static const unsigned long cp_single_171[] = {0x0190};
static const unsigned long cp_single_172[] = {0x0395};
static const unsigned long cp_single_173[] = {0x0388};
static const unsigned long cp_single_174[] = {0x0420};
static const unsigned long cp_single_175[] = {0x018e};
static const unsigned long cp_single_176[] = {0x042d};
static const unsigned long cp_single_177[] = {0x0421};
static const unsigned long cp_single_178[] = {0x04aa};
static const unsigned long cp_single_179[] = {0x01a9};
static const unsigned long cp_single_180[] = {0xf765};
static const unsigned long cp_single_181[] = {0x0397};
static const unsigned long cp_single_182[] = {0x0538};
static const unsigned long cp_single_183[] = {0x0389};
static const unsigned long cp_single_184[] = {0x00d0};
static const unsigned long cp_single_185[] = {0xf7f0};
static const unsigned long cp_single_186[] = {0x1ebc};
static const unsigned long cp_single_187[] = {0x1e1a};
static const unsigned long cp_single_188[] = {0x20ac};
static const unsigned long cp_single_189[] = {0x01b7};
static const unsigned long cp_single_190[] = {0x01ee};
static const unsigned long cp_single_191[] = {0x01b8};
static const unsigned long cp_single_192[] = {0x0046};
static const unsigned long cp_single_193[] = {0x24bb};
static const unsigned long cp_single_194[] = {0x1e1e};
static const unsigned long cp_single_195[] = {0x0556};
static const unsigned long cp_single_196[] = {0x03e4};
static const unsigned long cp_single_197[] = {0x0191};
static const unsigned long cp_single_198[] = {0x0472};
static const unsigned long cp_single_199[] = {0x2164};
static const unsigned long cp_single_200[] = {0xff26};
static const unsigned long cp_single_201[] = {0x2163};
static const unsigned long cp_single_202[] = {0xf766};
static const unsigned long cp_single_203[] = {0x0047};
static const unsigned long cp_single_204[] = {0x3387};
static const unsigned long cp_single_205[] = {0x01f4};
static const unsigned long cp_single_206[] = {0x0393};
static const unsigned long cp_single_207[] = {0x0194};
static const unsigned long cp_single_208[] = {0x03ea};
static const unsigned long cp_single_209[] = {0x011e};
static const unsigned long cp_single_210[] = {0x01e6};
static const unsigned long cp_single_211[] = {0x0122};
static const unsigned long cp_single_212[] = {0x24bc};
static const unsigned long cp_single_213[] = {0x011c};
static const unsigned long cp_single_214[] = {0x0122};
static const unsigned long cp_single_215[] = {0x0120};
static const unsigned long cp_single_216[] = {0x0120};
static const unsigned long cp_single_217[] = {0x0413};
static const unsigned long cp_single_218[] = {0x0542};
static const unsigned long cp_single_219[] = {0x0494};
static const unsigned long cp_single_220[] = {0x0492};
static const unsigned long cp_single_221[] = {0x0490};
static const unsigned long cp_single_222[] = {0x0193};
static const unsigned long cp_single_223[] = {0x0533};
static const unsigned long cp_single_224[] = {0x0403};
static const unsigned long cp_single_225[] = {0x1e20};
static const unsigned long cp_single_226[] = {0xff27};
static const unsigned long cp_single_227[] = {0xf6ce};
static const unsigned long cp_single_228[] = {0xf760};
static const unsigned long cp_single_229[] = {0xf767};
static const unsigned long cp_single_230[] = {0x029b};
static const unsigned long cp_single_231[] = {0x01e4};
static const unsigned long cp_single_232[] = {0x0048};
static const unsigned long cp_single_233[] = {0x25cf};
static const unsigned long cp_single_234[] = {0x25aa};
static const unsigned long cp_single_235[] = {0x25ab};
static const unsigned long cp_single_236[] = {0x25a1};
static const unsigned long cp_single_237[] = {0x33cb};
static const unsigned long cp_single_238[] = {0x04a8};
static const unsigned long cp_single_239[] = {0x04b2};
static const unsigned long cp_single_240[] = {0x042a};
static const unsigned long cp_single_241[] = {0x0126};
static const unsigned long cp_single_242[] = {0x1e2a};
static const unsigned long cp_single_243[] = {0x1e28};
static const unsigned long cp_single_244[] = {0x24bd};
static const unsigned long cp_single_245[] = {0x0124};
static const unsigned long cp_single_246[] = {0x1e26};
static const unsigned long cp_single_247[] = {0x1e22};
static const unsigned long cp_single_248[] = {0x1e24};
static const unsigned long cp_single_249[] = {0xff28};
static const unsigned long cp_single_250[] = {0x0540};
static const unsigned long cp_single_251[] = {0x03e8};
static const unsigned long cp_single_252[] = {0xf768};
static const unsigned long cp_single_253[] = {0xf6cf};
static const unsigned long cp_single_254[] = {0xf6f8};
static const unsigned long cp_single_255[] = {0x3390};
static const unsigned long cp_single_256[] = {0x0049};
static const unsigned long cp_single_257[] = {0x042f};
static const unsigned long cp_single_258[] = {0x0132};
static const unsigned long cp_single_259[] = {0x042e};
static const unsigned long cp_single_260[] = {0x00cd};
static const unsigned long cp_single_261[] = {0xf7ed};
static const unsigned long cp_single_262[] = {0x012c};
static const unsigned long cp_single_263[] = {0x01cf};
static const unsigned long cp_single_264[] = {0x24be};
static const unsigned long cp_single_265[] = {0x00ce};
static const unsigned long cp_single_266[] = {0xf7ee};
static const unsigned long cp_single_267[] = {0x0406};
static const unsigned long cp_single_268[] = {0x0208};
static const unsigned long cp_single_269[] = {0x00cf};
static const unsigned long cp_single_270[] = {0x1e2e};
static const unsigned long cp_single_271[] = {0x04e4};
static const unsigned long cp_single_272[] = {0xf7ef};
static const unsigned long cp_single_273[] = {0x0130};
static const unsigned long cp_single_274[] = {0x0130};
static const unsigned long cp_single_275[] = {0x1eca};
static const unsigned long cp_single_276[] = {0x04d6};
static const unsigned long cp_single_277[] = {0x0415};
static const unsigned long cp_single_278[] = {0x2111};
static const unsigned long cp_single_279[] = {0x00cc};
static const unsigned long cp_single_280[] = {0xf7ec};
static const unsigned long cp_single_281[] = {0x1ec8};
static const unsigned long cp_single_282[] = {0x0418};
static const unsigned long cp_single_283[] = {0x020a};
static const unsigned long cp_single_284[] = {0x0419};
static const unsigned long cp_single_285[] = {0x012a};
static const unsigned long cp_single_286[] = {0x04e2};
static const unsigned long cp_single_287[] = {0xff29};
static const unsigned long cp_single_288[] = {0x053b};
static const unsigned long cp_single_289[] = {0x0401};
static const unsigned long cp_single_290[] = {0x012e};
static const unsigned long cp_single_291[] = {0x0399};
static const unsigned long cp_single_292[] = {0x0196};
static const unsigned long cp_single_293[] = {0x03aa};
static const unsigned long cp_single_294[] = {0x038a};
static const unsigned long cp_single_295[] = {0xf769};
static const unsigned long cp_single_296[] = {0x0197};
static const unsigned long cp_single_297[] = {0x0128};
static const unsigned long cp_single_298[] = {0x1e2c};
static const unsigned long cp_single_299[] = {0x0474};
static const unsigned long cp_single_300[] = {0x0476};
static const unsigned long cp_single_301[] = {0x004a};
static const unsigned long cp_single_302[] = {0x0541};
static const unsigned long cp_single_303[] = {0x24bf};
static const unsigned long cp_single_304[] = {0x0134};
static const unsigned long cp_single_305[] = {0x0408};
static const unsigned long cp_single_306[] = {0x054b};
static const unsigned long cp_single_307[] = {0xff2a};
static const unsigned long cp_single_308[] = {0xf76a};
static const unsigned long cp_single_309[] = {0x004b};
static const unsigned long cp_single_310[] = {0x3385};
static const unsigned long cp_single_311[] = {0x33cd};
static const unsigned long cp_single_312[] = {0x04a0};
static const unsigned long cp_single_313[] = {0x1e30};
static const unsigned long cp_single_314[] = {0x041a};
static const unsigned long cp_single_315[] = {0x049a};
static const unsigned long cp_single_316[] = {0x04c3};
static const unsigned long cp_single_317[] = {0x039a};
static const unsigned long cp_single_318[] = {0x049e};
static const unsigned long cp_single_319[] = {0x049c};
static const unsigned long cp_single_320[] = {0x01e8};
static const unsigned long cp_single_321[] = {0x0136};
static const unsigned long cp_single_322[] = {0x24c0};
static const unsigned long cp_single_323[] = {0x0136};
static const unsigned long cp_single_324[] = {0x1e32};
static const unsigned long cp_single_325[] = {0x0554};
static const unsigned long cp_single_326[] = {0x053f};
static const unsigned long cp_single_327[] = {0x0425};
static const unsigned long cp_single_328[] = {0x03e6};
static const unsigned long cp_single_329[] = {0x0198};
static const unsigned long cp_single_330[] = {0x040c};
static const unsigned long cp_single_331[] = {0x1e34};
static const unsigned long cp_single_332[] = {0xff2b};
static const unsigned long cp_single_333[] = {0x0480};
static const unsigned long cp_single_334[] = {0x03de};
static const unsigned long cp_single_335[] = {0x046e};
static const unsigned long cp_single_336[] = {0xf76b};
static const unsigned long cp_single_337[] = {0x004c};
static const unsigned long cp_single_338[] = {0x01c7};
static const unsigned long cp_single_339[] = {0xf6bf};
static const unsigned long cp_single_340[] = {0x0139};
static const unsigned long cp_single_341[] = {0x039b};
static const unsigned long cp_single_342[] = {0x013d};
static const unsigned long cp_single_343[] = {0x013b};
static const unsigned long cp_single_344[] = {0x24c1};
static const unsigned long cp_single_345[] = {0x1e3c};
static const unsigned long cp_single_346[] = {0x013b};
static const unsigned long cp_single_347[] = {0x013f};
static const unsigned long cp_single_348[] = {0x013f};
static const unsigned long cp_single_349[] = {0x1e36};
static const unsigned long cp_single_350[] = {0x1e38};
static const unsigned long cp_single_351[] = {0x053c};
static const unsigned long cp_single_352[] = {0x01c8};
static const unsigned long cp_single_353[] = {0x0409};
static const unsigned long cp_single_354[] = {0x1e3a};
static const unsigned long cp_single_355[] = {0xff2c};
static const unsigned long cp_single_356[] = {0x0141};
static const unsigned long cp_single_357[] = {0xf6f9};
static const unsigned long cp_single_358[] = {0xf76c};
static const unsigned long cp_single_359[] = {0x004d};
static const unsigned long cp_single_360[] = {0x3386};
static const unsigned long cp_single_361[] = {0xf6d0};
static const unsigned long cp_single_362[] = {0xf7af};
static const unsigned long cp_single_363[] = {0x1e3e};
static const unsigned long cp_single_364[] = {0x24c2};
static const unsigned long cp_single_365[] = {0x1e40};
static const unsigned long cp_single_366[] = {0x1e42};
static const unsigned long cp_single_367[] = {0x0544};
static const unsigned long cp_single_368[] = {0xff2d};
static const unsigned long cp_single_369[] = {0xf76d};
static const unsigned long cp_single_370[] = {0x019c};
static const unsigned long cp_single_371[] = {0x039c};
static const unsigned long cp_single_372[] = {0x004e};
static const unsigned long cp_single_373[] = {0x01ca};
static const unsigned long cp_single_374[] = {0x0143};
static const unsigned long cp_single_375[] = {0x0147};
static const unsigned long cp_single_376[] = {0x0145};
static const unsigned long cp_single_377[] = {0x24c3};
static const unsigned long cp_single_378[] = {0x1e4a};
static const unsigned long cp_single_379[] = {0x0145};
static const unsigned long cp_single_380[] = {0x1e44};
static const unsigned long cp_single_381[] = {0x1e46};
static const unsigned long cp_single_382[] = {0x019d};
static const unsigned long cp_single_383[] = {0x2168};
static const unsigned long cp_single_384[] = {0x01cb};
static const unsigned long cp_single_385[] = {0x040a};
static const unsigned long cp_single_386[] = {0x1e48};
static const unsigned long cp_single_387[] = {0xff2e};
static const unsigned long cp_single_388[] = {0x0546};
static const unsigned long cp_single_389[] = {0xf76e};
static const unsigned long cp_single_390[] = {0x00d1};
static const unsigned long cp_single_391[] = {0xf7f1};
static const unsigned long cp_single_392[] = {0x039d};
static const unsigned long cp_single_393[] = {0x004f};
static const unsigned long cp_single_394[] = {0x0152};
static const unsigned long cp_single_395[] = {0xf6fa};
static const unsigned long cp_single_396[] = {0x00d3};
static const unsigned long cp_single_397[] = {0xf7f3};
static const unsigned long cp_single_398[] = {0x04e8};
static const unsigned long cp_single_399[] = {0x04ea};
static const unsigned long cp_single_400[] = {0x014e};
static const unsigned long cp_single_401[] = {0x01d1};
static const unsigned long cp_single_402[] = {0x019f};
static const unsigned long cp_single_403[] = {0x24c4};
static const unsigned long cp_single_404[] = {0x00d4};
static const unsigned long cp_single_405[] = {0x1ed0};
static const unsigned long cp_single_406[] = {0x1ed8};
static const unsigned long cp_single_407[] = {0x1ed2};
static const unsigned long cp_single_408[] = {0x1ed4};
static const unsigned long cp_single_409[] = {0xf7f4};
static const unsigned long cp_single_410[] = {0x1ed6};
static const unsigned long cp_single_411[] = {0x041e};
static const unsigned long cp_single_412[] = {0x0150};
static const unsigned long cp_single_413[] = {0x020c};
static const unsigned long cp_single_414[] = {0x00d6};
static const unsigned long cp_single_415[] = {0x04e6};
static const unsigned long cp_single_416[] = {0xf7f6};
static const unsigned long cp_single_417[] = {0x1ecc};
static const unsigned long cp_single_418[] = {0xf6fb};
static const unsigned long cp_single_419[] = {0x00d2};
static const unsigned long cp_single_420[] = {0xf7f2};
static const unsigned long cp_single_421[] = {0x0555};
static const unsigned long cp_single_422[] = {0x2126};
static const unsigned long cp_single_423[] = {0x1ece};
static const unsigned long cp_single_424[] = {0x01a0};
static const unsigned long cp_single_425[] = {0x1eda};
static const unsigned long cp_single_426[] = {0x1ee2};
static const unsigned long cp_single_427[] = {0x1edc};
static const unsigned long cp_single_428[] = {0x1ede};
static const unsigned long cp_single_429[] = {0x1ee0};
static const unsigned long cp_single_430[] = {0x0150};
static const unsigned long cp_single_431[] = {0x01a2};
static const unsigned long cp_single_432[] = {0x020e};
static const unsigned long cp_single_433[] = {0x014c};
static const unsigned long cp_single_434[] = {0x1e52};
static const unsigned long cp_single_435[] = {0x1e50};
static const unsigned long cp_single_436[] = {0x2126};
static const unsigned long cp_single_437[] = {0x0460};
static const unsigned long cp_single_438[] = {0x03a9};
static const unsigned long cp_single_439[] = {0x047a};
static const unsigned long cp_single_440[] = {0x047c};
static const unsigned long cp_single_441[] = {0x038f};
static const unsigned long cp_single_442[] = {0x039f};
static const unsigned long cp_single_443[] = {0x038c};
static const unsigned long cp_single_444[] = {0xff2f};
static const unsigned long cp_single_445[] = {0x2160};
static const unsigned long cp_single_446[] = {0x01ea};
static const unsigned long cp_single_447[] = {0x01ec};
static const unsigned long cp_single_448[] = {0x0186};
static const unsigned long cp_single_449[] = {0x00d8};
static const unsigned long cp_single_450[] = {0x01fe};
static const unsigned long cp_single_451[] = {0xf7f8};
static const unsigned long cp_single_452[] = {0xf76f};
static const unsigned long cp_single_453[] = {0x01fe};
static const unsigned long cp_single_454[] = {0x047e};
static const unsigned long cp_single_455[] = {0x00d5};
static const unsigned long cp_single_456[] = {0x1e4c};
static const unsigned long cp_single_457[] = {0x1e4e};
static const unsigned long cp_single_458[] = {0xf7f5};
static const unsigned long cp_single_459[] = {0x0050};
static const unsigned long cp_single_460[] = {0x1e54};
static const unsigned long cp_single_461[] = {0x24c5};
static const unsigned long cp_single_462[] = {0x1e56};
static const unsigned long cp_single_463[] = {0x041f};
static const unsigned long cp_single_464[] = {0x054a};
static const unsigned long cp_single_465[] = {0x04a6};
static const unsigned long cp_single_466[] = {0x03a6};
static const unsigned long cp_single_467[] = {0x01a4};
static const unsigned long cp_single_468[] = {0x03a0};
static const unsigned long cp_single_469[] = {0x0553};
static const unsigned long cp_single_470[] = {0xff30};
static const unsigned long cp_single_471[] = {0x03a8};
static const unsigned long cp_single_472[] = {0x0470};
static const unsigned long cp_single_473[] = {0xf770};
static const unsigned long cp_single_474[] = {0x0051};
static const unsigned long cp_single_475[] = {0x24c6};
static const unsigned long cp_single_476[] = {0xff31};
static const unsigned long cp_single_477[] = {0xf771};
static const unsigned long cp_single_478[] = {0x0052};
static const unsigned long cp_single_479[] = {0x054c};
static const unsigned long cp_single_480[] = {0x0154};
static const unsigned long cp_single_481[] = {0x0158};
static const unsigned long cp_single_482[] = {0x0156};
static const unsigned long cp_single_483[] = {0x24c7};
static const unsigned long cp_single_484[] = {0x0156};
static const unsigned long cp_single_485[] = {0x0210};
static const unsigned long cp_single_486[] = {0x1e58};
static const unsigned long cp_single_487[] = {0x1e5a};
static const unsigned long cp_single_488[] = {0x1e5c};
static const unsigned long cp_single_489[] = {0x0550};
static const unsigned long cp_single_490[] = {0x211c};
static const unsigned long cp_single_491[] = {0x03a1};
static const unsigned long cp_single_492[] = {0xf6fc};
static const unsigned long cp_single_493[] = {0x0212};
static const unsigned long cp_single_494[] = {0x1e5e};
static const unsigned long cp_single_495[] = {0xff32};
static const unsigned long cp_single_496[] = {0xf772};
static const unsigned long cp_single_497[] = {0x0281};
static const unsigned long cp_single_498[] = {0x02b6};
static const unsigned long cp_single_499[] = {0x0053};
static const unsigned long cp_single_500[] = {0x250c};
static const unsigned long cp_single_501[] = {0x2514};
static const unsigned long cp_single_502[] = {0x2510};
static const unsigned long cp_single_503[] = {0x2518};
static const unsigned long cp_single_504[] = {0x253c};
static const unsigned long cp_single_505[] = {0x252c};
static const unsigned long cp_single_506[] = {0x2534};
static const unsigned long cp_single_507[] = {0x251c};
static const unsigned long cp_single_508[] = {0x2524};
static const unsigned long cp_single_509[] = {0x2500};
static const unsigned long cp_single_510[] = {0x2502};
static const unsigned long cp_single_511[] = {0x2561};
static const unsigned long cp_single_512[] = {0x2562};
static const unsigned long cp_single_513[] = {0x2556};
static const unsigned long cp_single_514[] = {0x2555};
static const unsigned long cp_single_515[] = {0x2563};
static const unsigned long cp_single_516[] = {0x2551};
static const unsigned long cp_single_517[] = {0x2557};
static const unsigned long cp_single_518[] = {0x255d};
static const unsigned long cp_single_519[] = {0x255c};
static const unsigned long cp_single_520[] = {0x255b};
static const unsigned long cp_single_521[] = {0x255e};
static const unsigned long cp_single_522[] = {0x255f};
static const unsigned long cp_single_523[] = {0x255a};
static const unsigned long cp_single_524[] = {0x2554};
static const unsigned long cp_single_525[] = {0x2569};
static const unsigned long cp_single_526[] = {0x2566};
static const unsigned long cp_single_527[] = {0x2560};
static const unsigned long cp_single_528[] = {0x2550};
static const unsigned long cp_single_529[] = {0x256c};
static const unsigned long cp_single_530[] = {0x2567};
static const unsigned long cp_single_531[] = {0x2568};
static const unsigned long cp_single_532[] = {0x2564};
static const unsigned long cp_single_533[] = {0x2565};
static const unsigned long cp_single_534[] = {0x2559};
static const unsigned long cp_single_535[] = {0x2558};
static const unsigned long cp_single_536[] = {0x2552};
static const unsigned long cp_single_537[] = {0x2553};
static const unsigned long cp_single_538[] = {0x256b};
static const unsigned long cp_single_539[] = {0x256a};
static const unsigned long cp_single_540[] = {0x015a};
static const unsigned long cp_single_541[] = {0x1e64};
static const unsigned long cp_single_542[] = {0x03e0};
static const unsigned long cp_single_543[] = {0x0160};
static const unsigned long cp_single_544[] = {0x1e66};
static const unsigned long cp_single_545[] = {0xf6fd};
static const unsigned long cp_single_546[] = {0x015e};
static const unsigned long cp_single_547[] = {0x018f};
static const unsigned long cp_single_548[] = {0x04d8};
static const unsigned long cp_single_549[] = {0x04da};
static const unsigned long cp_single_550[] = {0x24c8};
static const unsigned long cp_single_551[] = {0x015c};
static const unsigned long cp_single_552[] = {0x0218};
static const unsigned long cp_single_553[] = {0x1e60};
static const unsigned long cp_single_554[] = {0x1e62};
static const unsigned long cp_single_555[] = {0x1e68};
static const unsigned long cp_single_556[] = {0x054d};
static const unsigned long cp_single_557[] = {0x2166};
static const unsigned long cp_single_558[] = {0x0547};
static const unsigned long cp_single_559[] = {0x0428};
static const unsigned long cp_single_560[] = {0x0429};
static const unsigned long cp_single_561[] = {0x03e2};
static const unsigned long cp_single_562[] = {0x04ba};
static const unsigned long cp_single_563[] = {0x03ec};
static const unsigned long cp_single_564[] = {0x03a3};
static const unsigned long cp_single_565[] = {0x2165};
static const unsigned long cp_single_566[] = {0xff33};
static const unsigned long cp_single_567[] = {0x042c};
static const unsigned long cp_single_568[] = {0xf773};
static const unsigned long cp_single_569[] = {0x03da};
static const unsigned long cp_single_570[] = {0x0054};
static const unsigned long cp_single_571[] = {0x03a4};
static const unsigned long cp_single_572[] = {0x0166};
static const unsigned long cp_single_573[] = {0x0164};
static const unsigned long cp_single_574[] = {0x0162};
static const unsigned long cp_single_575[] = {0x24c9};
static const unsigned long cp_single_576[] = {0x1e70};
static const unsigned long cp_single_577[] = {0x0162};
static const unsigned long cp_single_578[] = {0x1e6a};
static const unsigned long cp_single_579[] = {0x1e6c};
static const unsigned long cp_single_580[] = {0x0422};
static const unsigned long cp_single_581[] = {0x04ac};
static const unsigned long cp_single_582[] = {0x2169};
static const unsigned long cp_single_583[] = {0x04b4};
static const unsigned long cp_single_584[] = {0x0398};
static const unsigned long cp_single_585[] = {0x01ac};
static const unsigned long cp_single_586[] = {0x00de};
static const unsigned long cp_single_587[] = {0xf7fe};
static const unsigned long cp_single_588[] = {0x2162};
static const unsigned long cp_single_589[] = {0xf6fe};
static const unsigned long cp_single_590[] = {0x054f};
static const unsigned long cp_single_591[] = {0x1e6e};
static const unsigned long cp_single_592[] = {0xff34};
static const unsigned long cp_single_593[] = {0x0539};
static const unsigned long cp_single_594[] = {0x01bc};
static const unsigned long cp_single_595[] = {0x0184};
static const unsigned long cp_single_596[] = {0x01a7};
static const unsigned long cp_single_597[] = {0x01ae};
static const unsigned long cp_single_598[] = {0x0426};
static const unsigned long cp_single_599[] = {0x040b};
static const unsigned long cp_single_600[] = {0xf774};
static const unsigned long cp_single_601[] = {0x216b};
static const unsigned long cp_single_602[] = {0x2161};
static const unsigned long cp_single_603[] = {0x0055};
static const unsigned long cp_single_604[] = {0x00da};
static const unsigned long cp_single_605[] = {0xf7fa};
static const unsigned long cp_single_606[] = {0x016c};
static const unsigned long cp_single_607[] = {0x01d3};
static const unsigned long cp_single_608[] = {0x24ca};
static const unsigned long cp_single_609[] = {0x00db};
static const unsigned long cp_single_610[] = {0x1e76};
static const unsigned long cp_single_611[] = {0xf7fb};
static const unsigned long cp_single_612[] = {0x0423};
static const unsigned long cp_single_613[] = {0x0170};
static const unsigned long cp_single_614[] = {0x0214};
static const unsigned long cp_single_615[] = {0x00dc};
static const unsigned long cp_single_616[] = {0x01d7};
static const unsigned long cp_single_617[] = {0x1e72};
static const unsigned long cp_single_618[] = {0x01d9};
static const unsigned long cp_single_619[] = {0x04f0};
static const unsigned long cp_single_620[] = {0x01db};
static const unsigned long cp_single_621[] = {0x01d5};
static const unsigned long cp_single_622[] = {0xf7fc};
static const unsigned long cp_single_623[] = {0x1ee4};
static const unsigned long cp_single_624[] = {0x00d9};
static const unsigned long cp_single_625[] = {0xf7f9};
static const unsigned long cp_single_626[] = {0x1ee6};
static const unsigned long cp_single_627[] = {0x01af};
static const unsigned long cp_single_628[] = {0x1ee8};
static const unsigned long cp_single_629[] = {0x1ef0};
static const unsigned long cp_single_630[] = {0x1eea};
static const unsigned long cp_single_631[] = {0x1eec};
static const unsigned long cp_single_632[] = {0x1eee};
static const unsigned long cp_single_633[] = {0x0170};
static const unsigned long cp_single_634[] = {0x04f2};
static const unsigned long cp_single_635[] = {0x0216};
static const unsigned long cp_single_636[] = {0x0478};
static const unsigned long cp_single_637[] = {0x016a};
static const unsigned long cp_single_638[] = {0x04ee};
static const unsigned long cp_single_639[] = {0x1e7a};
static const unsigned long cp_single_640[] = {0xff35};
static const unsigned long cp_single_641[] = {0x0172};
static const unsigned long cp_single_642[] = {0x03a5};
static const unsigned long cp_single_643[] = {0x03d2};
static const unsigned long cp_single_644[] = {0x03d3};
static const unsigned long cp_single_645[] = {0x01b1};
static const unsigned long cp_single_646[] = {0x03ab};
static const unsigned long cp_single_647[] = {0x03d4};
static const unsigned long cp_single_648[] = {0x03d2};
static const unsigned long cp_single_649[] = {0x038e};
static const unsigned long cp_single_650[] = {0x016e};
static const unsigned long cp_single_651[] = {0x040e};
static const unsigned long cp_single_652[] = {0xf775};
static const unsigned long cp_single_653[] = {0x04ae};
static const unsigned long cp_single_654[] = {0x04b0};
static const unsigned long cp_single_655[] = {0x0168};
static const unsigned long cp_single_656[] = {0x1e78};
static const unsigned long cp_single_657[] = {0x1e74};
static const unsigned long cp_single_658[] = {0x0056};
static const unsigned long cp_single_659[] = {0x24cb};
static const unsigned long cp_single_660[] = {0x1e7e};
static const unsigned long cp_single_661[] = {0x0412};
static const unsigned long cp_single_662[] = {0x054e};
static const unsigned long cp_single_663[] = {0x01b2};
static const unsigned long cp_single_664[] = {0xff36};
static const unsigned long cp_single_665[] = {0x0548};
static const unsigned long cp_single_666[] = {0xf776};
static const unsigned long cp_single_667[] = {0x1e7c};
static const unsigned long cp_single_668[] = {0x0057};
static const unsigned long cp_single_669[] = {0x1e82};
static const unsigned long cp_single_670[] = {0x24cc};
static const unsigned long cp_single_671[] = {0x0174};
static const unsigned long cp_single_672[] = {0x1e84};
static const unsigned long cp_single_673[] = {0x1e86};
static const unsigned long cp_single_674[] = {0x1e88};
static const unsigned long cp_single_675[] = {0x1e80};
static const unsigned long cp_single_676[] = {0xff37};
static const unsigned long cp_single_677[] = {0xf777};
static const unsigned long cp_single_678[] = {0x0058};
static const unsigned long cp_single_679[] = {0x24cd};
static const unsigned long cp_single_680[] = {0x1e8c};
static const unsigned long cp_single_681[] = {0x1e8a};
static const unsigned long cp_single_682[] = {0x053d};
static const unsigned long cp_single_683[] = {0x039e};
static const unsigned long cp_single_684[] = {0xff38};
static const unsigned long cp_single_685[] = {0xf778};
static const unsigned long cp_single_686[] = {0x0059};
static const unsigned long cp_single_687[] = {0x00dd};
static const unsigned long cp_single_688[] = {0xf7fd};
static const unsigned long cp_single_689[] = {0x0462};
static const unsigned long cp_single_690[] = {0x24ce};
static const unsigned long cp_single_691[] = {0x0176};
static const unsigned long cp_single_692[] = {0x0178};
static const unsigned long cp_single_693[] = {0xf7ff};
static const unsigned long cp_single_694[] = {0x1e8e};
static const unsigned long cp_single_695[] = {0x1ef4};
static const unsigned long cp_single_696[] = {0x042b};
static const unsigned long cp_single_697[] = {0x04f8};
static const unsigned long cp_single_698[] = {0x1ef2};
static const unsigned long cp_single_699[] = {0x01b3};
static const unsigned long cp_single_700[] = {0x1ef6};
static const unsigned long cp_single_701[] = {0x0545};
static const unsigned long cp_single_702[] = {0x0407};
static const unsigned long cp_single_703[] = {0x0552};
static const unsigned long cp_single_704[] = {0xff39};
static const unsigned long cp_single_705[] = {0xf779};
static const unsigned long cp_single_706[] = {0x1ef8};
static const unsigned long cp_single_707[] = {0x046a};
static const unsigned long cp_single_708[] = {0x046c};
static const unsigned long cp_single_709[] = {0x0466};
static const unsigned long cp_single_710[] = {0x0468};
static const unsigned long cp_single_711[] = {0x005a};
static const unsigned long cp_single_712[] = {0x0536};
static const unsigned long cp_single_713[] = {0x0179};
static const unsigned long cp_single_714[] = {0x017d};
static const unsigned long cp_single_715[] = {0xf6ff};
static const unsigned long cp_single_716[] = {0x24cf};
static const unsigned long cp_single_717[] = {0x1e90};
static const unsigned long cp_single_718[] = {0x017b};
static const unsigned long cp_single_719[] = {0x017b};
static const unsigned long cp_single_720[] = {0x1e92};
static const unsigned long cp_single_721[] = {0x0417};
static const unsigned long cp_single_722[] = {0x0498};
static const unsigned long cp_single_723[] = {0x04de};
static const unsigned long cp_single_724[] = {0x0396};
static const unsigned long cp_single_725[] = {0x053a};
static const unsigned long cp_single_726[] = {0x04c1};
static const unsigned long cp_single_727[] = {0x0416};
static const unsigned long cp_single_728[] = {0x0496};
static const unsigned long cp_single_729[] = {0x04dc};
static const unsigned long cp_single_730[] = {0x1e94};
static const unsigned long cp_single_731[] = {0xff3a};
static const unsigned long cp_single_732[] = {0xf77a};
static const unsigned long cp_single_733[] = {0x01b5};
static const unsigned long cp_single_734[] = {0x0061};
static const unsigned long cp_single_735[] = {0x0986};
static const unsigned long cp_single_736[] = {0x00e1};
static const unsigned long cp_single_737[] = {0x0906};
static const unsigned long cp_single_738[] = {0x0a86};
static const unsigned long cp_single_739[] = {0x0a06};
static const unsigned long cp_single_740[] = {0x0a3e};
static const unsigned long cp_single_741[] = {0x3303};
static const unsigned long cp_single_742[] = {0x09be};
static const unsigned long cp_single_743[] = {0x093e};
static const unsigned long cp_single_744[] = {0x0abe};
static const unsigned long cp_single_745[] = {0x055f};
static const unsigned long cp_single_746[] = {0x0970};
static const unsigned long cp_single_747[] = {0x0985};
static const unsigned long cp_single_748[] = {0x311a};
static const unsigned long cp_single_749[] = {0x0103};
static const unsigned long cp_single_750[] = {0x1eaf};
static const unsigned long cp_single_751[] = {0x04d1};
static const unsigned long cp_single_752[] = {0x1eb7};
static const unsigned long cp_single_753[] = {0x1eb1};
static const unsigned long cp_single_754[] = {0x1eb3};
static const unsigned long cp_single_755[] = {0x1eb5};
static const unsigned long cp_single_756[] = {0x01ce};
static const unsigned long cp_single_757[] = {0x24d0};
static const unsigned long cp_single_758[] = {0x00e2};
static const unsigned long cp_single_759[] = {0x1ea5};
static const unsigned long cp_single_760[] = {0x1ead};
static const unsigned long cp_single_761[] = {0x1ea7};
static const unsigned long cp_single_762[] = {0x1ea9};
static const unsigned long cp_single_763[] = {0x1eab};
static const unsigned long cp_single_764[] = {0x00b4};
static const unsigned long cp_single_765[] = {0x0317};
static const unsigned long cp_single_766[] = {0x0301};
static const unsigned long cp_single_767[] = {0x0301};
static const unsigned long cp_single_768[] = {0x0954};
static const unsigned long cp_single_769[] = {0x02cf};
static const unsigned long cp_single_770[] = {0x0341};
static const unsigned long cp_single_771[] = {0x0430};
static const unsigned long cp_single_772[] = {0x0201};
static const unsigned long cp_single_773[] = {0x0a71};
static const unsigned long cp_single_774[] = {0x0905};
static const unsigned long cp_single_775[] = {0x00e4};
static const unsigned long cp_single_776[] = {0x04d3};
static const unsigned long cp_single_777[] = {0x01df};
static const unsigned long cp_single_778[] = {0x1ea1};
static const unsigned long cp_single_779[] = {0x01e1};
static const unsigned long cp_single_780[] = {0x00e6};
static const unsigned long cp_single_781[] = {0x01fd};
static const unsigned long cp_single_782[] = {0x3150};
static const unsigned long cp_single_783[] = {0x01e3};
static const unsigned long cp_single_784[] = {0x2015};
static const unsigned long cp_single_785[] = {0x20a4};
static const unsigned long cp_single_786[] = {0x0410};
static const unsigned long cp_single_787[] = {0x0411};
static const unsigned long cp_single_788[] = {0x0412};
static const unsigned long cp_single_789[] = {0x0413};
static const unsigned long cp_single_790[] = {0x0414};
static const unsigned long cp_single_791[] = {0x0415};
static const unsigned long cp_single_792[] = {0x0401};
static const unsigned long cp_single_793[] = {0x0416};
static const unsigned long cp_single_794[] = {0x0417};
static const unsigned long cp_single_795[] = {0x0418};
static const unsigned long cp_single_796[] = {0x0419};
static const unsigned long cp_single_797[] = {0x041a};
static const unsigned long cp_single_798[] = {0x041b};
static const unsigned long cp_single_799[] = {0x041c};
static const unsigned long cp_single_800[] = {0x041d};
static const unsigned long cp_single_801[] = {0x041e};
static const unsigned long cp_single_802[] = {0x041f};
static const unsigned long cp_single_803[] = {0x0420};
static const unsigned long cp_single_804[] = {0x0421};
static const unsigned long cp_single_805[] = {0x0422};
static const unsigned long cp_single_806[] = {0x0423};
static const unsigned long cp_single_807[] = {0x0424};
static const unsigned long cp_single_808[] = {0x0425};
static const unsigned long cp_single_809[] = {0x0426};
static const unsigned long cp_single_810[] = {0x0427};
static const unsigned long cp_single_811[] = {0x0428};
static const unsigned long cp_single_812[] = {0x0429};
static const unsigned long cp_single_813[] = {0x042a};
static const unsigned long cp_single_814[] = {0x042b};
static const unsigned long cp_single_815[] = {0x042c};
static const unsigned long cp_single_816[] = {0x042d};
static const unsigned long cp_single_817[] = {0x042e};
static const unsigned long cp_single_818[] = {0x042f};
static const unsigned long cp_single_819[] = {0x0490};
static const unsigned long cp_single_820[] = {0x0402};
static const unsigned long cp_single_821[] = {0x0403};
static const unsigned long cp_single_822[] = {0x0404};
static const unsigned long cp_single_823[] = {0x0405};
static const unsigned long cp_single_824[] = {0x0406};
static const unsigned long cp_single_825[] = {0x0407};
static const unsigned long cp_single_826[] = {0x0408};
static const unsigned long cp_single_827[] = {0x0409};
static const unsigned long cp_single_828[] = {0x040a};
static const unsigned long cp_single_829[] = {0x040b};
static const unsigned long cp_single_830[] = {0x040c};
static const unsigned long cp_single_831[] = {0x040e};
static const unsigned long cp_single_832[] = {0xf6c4};
static const unsigned long cp_single_833[] = {0xf6c5};
static const unsigned long cp_single_834[] = {0x0430};
static const unsigned long cp_single_835[] = {0x0431};
static const unsigned long cp_single_836[] = {0x0432};
static const unsigned long cp_single_837[] = {0x0433};
static const unsigned long cp_single_838[] = {0x0434};
static const unsigned long cp_single_839[] = {0x0435};
static const unsigned long cp_single_840[] = {0x0451};
static const unsigned long cp_single_841[] = {0x0436};
static const unsigned long cp_single_842[] = {0x0437};
static const unsigned long cp_single_843[] = {0x0438};
static const unsigned long cp_single_844[] = {0x0439};
static const unsigned long cp_single_845[] = {0x043a};
static const unsigned long cp_single_846[] = {0x043b};
static const unsigned long cp_single_847[] = {0x043c};
static const unsigned long cp_single_848[] = {0x043d};
static const unsigned long cp_single_849[] = {0x043e};
static const unsigned long cp_single_850[] = {0x043f};
static const unsigned long cp_single_851[] = {0x0440};
static const unsigned long cp_single_852[] = {0x0441};
static const unsigned long cp_single_853[] = {0x0442};
static const unsigned long cp_single_854[] = {0x0443};
static const unsigned long cp_single_855[] = {0x0444};
static const unsigned long cp_single_856[] = {0x0445};
static const unsigned long cp_single_857[] = {0x0446};
static const unsigned long cp_single_858[] = {0x0447};
static const unsigned long cp_single_859[] = {0x0448};
static const unsigned long cp_single_860[] = {0x0449};
static const unsigned long cp_single_861[] = {0x044a};
static const unsigned long cp_single_862[] = {0x044b};
static const unsigned long cp_single_863[] = {0x044c};
static const unsigned long cp_single_864[] = {0x044d};
static const unsigned long cp_single_865[] = {0x044e};
static const unsigned long cp_single_866[] = {0x044f};
static const unsigned long cp_single_867[] = {0x0491};
static const unsigned long cp_single_868[] = {0x0452};
static const unsigned long cp_single_869[] = {0x0453};
static const unsigned long cp_single_870[] = {0x0454};
static const unsigned long cp_single_871[] = {0x0455};
static const unsigned long cp_single_872[] = {0x0456};
static const unsigned long cp_single_873[] = {0x0457};
static const unsigned long cp_single_874[] = {0x0458};
static const unsigned long cp_single_875[] = {0x0459};
static const unsigned long cp_single_876[] = {0x045a};
static const unsigned long cp_single_877[] = {0x045b};
static const unsigned long cp_single_878[] = {0x045c};
static const unsigned long cp_single_879[] = {0x045e};
static const unsigned long cp_single_880[] = {0x040f};
static const unsigned long cp_single_881[] = {0x0462};
static const unsigned long cp_single_882[] = {0x0472};
static const unsigned long cp_single_883[] = {0x0474};
static const unsigned long cp_single_884[] = {0xf6c6};
static const unsigned long cp_single_885[] = {0x045f};
static const unsigned long cp_single_886[] = {0x0463};
static const unsigned long cp_single_887[] = {0x0473};
static const unsigned long cp_single_888[] = {0x0475};
static const unsigned long cp_single_889[] = {0xf6c7};
static const unsigned long cp_single_890[] = {0xf6c8};
static const unsigned long cp_single_891[] = {0x04d9};
static const unsigned long cp_single_892[] = {0x200e};
static const unsigned long cp_single_893[] = {0x200f};
static const unsigned long cp_single_894[] = {0x200d};
static const unsigned long cp_single_895[] = {0x066a};
static const unsigned long cp_single_896[] = {0x060c};
static const unsigned long cp_single_897[] = {0x0660};
static const unsigned long cp_single_898[] = {0x0661};
static const unsigned long cp_single_899[] = {0x0662};
static const unsigned long cp_single_900[] = {0x0663};
static const unsigned long cp_single_901[] = {0x0664};
static const unsigned long cp_single_902[] = {0x0665};
static const unsigned long cp_single_903[] = {0x0666};
static const unsigned long cp_single_904[] = {0x0667};
static const unsigned long cp_single_905[] = {0x0668};
static const unsigned long cp_single_906[] = {0x0669};
static const unsigned long cp_single_907[] = {0x061b};
static const unsigned long cp_single_908[] = {0x061f};
static const unsigned long cp_single_909[] = {0x0621};
static const unsigned long cp_single_910[] = {0x0622};
static const unsigned long cp_single_911[] = {0x0623};
static const unsigned long cp_single_912[] = {0x0624};
static const unsigned long cp_single_913[] = {0x0625};
static const unsigned long cp_single_914[] = {0x0626};
static const unsigned long cp_single_915[] = {0x0627};
static const unsigned long cp_single_916[] = {0x0628};
static const unsigned long cp_single_917[] = {0x0629};
static const unsigned long cp_single_918[] = {0x062a};
static const unsigned long cp_single_919[] = {0x062b};
static const unsigned long cp_single_920[] = {0x062c};
static const unsigned long cp_single_921[] = {0x062d};
static const unsigned long cp_single_922[] = {0x062e};
static const unsigned long cp_single_923[] = {0x062f};
static const unsigned long cp_single_924[] = {0x0630};
static const unsigned long cp_single_925[] = {0x0631};
static const unsigned long cp_single_926[] = {0x0632};
static const unsigned long cp_single_927[] = {0x0633};
static const unsigned long cp_single_928[] = {0x0634};
static const unsigned long cp_single_929[] = {0x0635};
static const unsigned long cp_single_930[] = {0x0636};
static const unsigned long cp_single_931[] = {0x0637};
static const unsigned long cp_single_932[] = {0x0638};
static const unsigned long cp_single_933[] = {0x0639};
static const unsigned long cp_single_934[] = {0x063a};
static const unsigned long cp_single_935[] = {0x0640};
static const unsigned long cp_single_936[] = {0x0641};
static const unsigned long cp_single_937[] = {0x0642};
static const unsigned long cp_single_938[] = {0x0643};
static const unsigned long cp_single_939[] = {0x0644};
static const unsigned long cp_single_940[] = {0x0645};
static const unsigned long cp_single_941[] = {0x0646};
static const unsigned long cp_single_942[] = {0x0648};
static const unsigned long cp_single_943[] = {0x0649};
static const unsigned long cp_single_944[] = {0x064a};
static const unsigned long cp_single_945[] = {0x064b};
static const unsigned long cp_single_946[] = {0x064c};
static const unsigned long cp_single_947[] = {0x064d};
static const unsigned long cp_single_948[] = {0x064e};
static const unsigned long cp_single_949[] = {0x064f};
static const unsigned long cp_single_950[] = {0x0650};
static const unsigned long cp_single_951[] = {0x0651};
static const unsigned long cp_single_952[] = {0x0652};
static const unsigned long cp_single_953[] = {0x0647};
static const unsigned long cp_single_954[] = {0x06a4};
static const unsigned long cp_single_955[] = {0x067e};
static const unsigned long cp_single_956[] = {0x0686};
static const unsigned long cp_single_957[] = {0x0698};
static const unsigned long cp_single_958[] = {0x06af};
static const unsigned long cp_single_959[] = {0x0679};
static const unsigned long cp_single_960[] = {0x0688};
static const unsigned long cp_single_961[] = {0x0691};
static const unsigned long cp_single_962[] = {0x06ba};
static const unsigned long cp_single_963[] = {0x06d2};
static const unsigned long cp_single_964[] = {0x06d5};
static const unsigned long cp_single_965[] = {0x20aa};
static const unsigned long cp_single_966[] = {0x05be};
static const unsigned long cp_single_967[] = {0x05c3};
static const unsigned long cp_single_968[] = {0x05d0};
static const unsigned long cp_single_969[] = {0x05d1};
static const unsigned long cp_single_970[] = {0x05d2};
static const unsigned long cp_single_971[] = {0x05d3};
static const unsigned long cp_single_972[] = {0x05d4};
static const unsigned long cp_single_973[] = {0x05d5};
static const unsigned long cp_single_974[] = {0x05d6};
static const unsigned long cp_single_975[] = {0x05d7};
static const unsigned long cp_single_976[] = {0x05d8};
static const unsigned long cp_single_977[] = {0x05d9};
static const unsigned long cp_single_978[] = {0x05da};
static const unsigned long cp_single_979[] = {0x05db};
static const unsigned long cp_single_980[] = {0x05dc};
static const unsigned long cp_single_981[] = {0x05dd};
static const unsigned long cp_single_982[] = {0x05de};
static const unsigned long cp_single_983[] = {0x05df};
static const unsigned long cp_single_984[] = {0x05e0};
static const unsigned long cp_single_985[] = {0x05e1};
static const unsigned long cp_single_986[] = {0x05e2};
static const unsigned long cp_single_987[] = {0x05e3};
static const unsigned long cp_single_988[] = {0x05e4};
static const unsigned long cp_single_989[] = {0x05e5};
static const unsigned long cp_single_990[] = {0x05e6};
static const unsigned long cp_single_991[] = {0x05e7};
static const unsigned long cp_single_992[] = {0x05e8};
static const unsigned long cp_single_993[] = {0x05e9};
static const unsigned long cp_single_994[] = {0x05ea};
static const unsigned long cp_single_995[] = {0xfb2a};
static const unsigned long cp_single_996[] = {0xfb2b};
static const unsigned long cp_single_997[] = {0xfb4b};
static const unsigned long cp_single_998[] = {0xfb1f};
static const unsigned long cp_single_999[] = {0x05f0};
static const unsigned long cp_single_1000[] = {0x05f1};
static const unsigned long cp_single_1001[] = {0x05f2};
static const unsigned long cp_single_1002[] = {0xfb35};
static const unsigned long cp_single_1003[] = {0x05b4};
static const unsigned long cp_single_1004[] = {0x05b5};
static const unsigned long cp_single_1005[] = {0x05b6};
static const unsigned long cp_single_1006[] = {0x05bb};
static const unsigned long cp_single_1007[] = {0x05b8};
static const unsigned long cp_single_1008[] = {0x05b7};
static const unsigned long cp_single_1009[] = {0x05b0};
static const unsigned long cp_single_1010[] = {0x05b2};
static const unsigned long cp_single_1011[] = {0x05b1};
static const unsigned long cp_single_1012[] = {0x05b3};
static const unsigned long cp_single_1013[] = {0x05c2};
static const unsigned long cp_single_1014[] = {0x05c1};
static const unsigned long cp_single_1015[] = {0x05b9};
static const unsigned long cp_single_1016[] = {0x05bc};
static const unsigned long cp_single_1017[] = {0x05bd};
static const unsigned long cp_single_1018[] = {0x05bf};
static const unsigned long cp_single_1019[] = {0x05c0};
static const unsigned long cp_single_1020[] = {0x02bc};
static const unsigned long cp_single_1021[] = {0x2105};
static const unsigned long cp_single_1022[] = {0x2113};
static const unsigned long cp_single_1023[] = {0x2116};
static const unsigned long cp_single_1024[] = {0x202c};
static const unsigned long cp_single_1025[] = {0x202d};
static const unsigned long cp_single_1026[] = {0x202e};
static const unsigned long cp_single_1027[] = {0x200c};
static const unsigned long cp_single_1028[] = {0x066d};
static const unsigned long cp_single_1029[] = {0x02bd};
static const unsigned long cp_single_1030[] = {0x00e0};
static const unsigned long cp_single_1031[] = {0x0a85};
static const unsigned long cp_single_1032[] = {0x0a05};
static const unsigned long cp_single_1033[] = {0x3042};
static const unsigned long cp_single_1034[] = {0x1ea3};
static const unsigned long cp_single_1035[] = {0x0990};
static const unsigned long cp_single_1036[] = {0x311e};
static const unsigned long cp_single_1037[] = {0x0910};
static const unsigned long cp_single_1038[] = {0x04d5};
static const unsigned long cp_single_1039[] = {0x0a90};
static const unsigned long cp_single_1040[] = {0x0a10};
static const unsigned long cp_single_1041[] = {0x0a48};
static const unsigned long cp_single_1042[] = {0x0639};
static const unsigned long cp_single_1043[] = {0xfeca};
static const unsigned long cp_single_1044[] = {0xfecb};
static const unsigned long cp_single_1045[] = {0xfecc};
static const unsigned long cp_single_1046[] = {0x0203};
static const unsigned long cp_single_1047[] = {0x09c8};
static const unsigned long cp_single_1048[] = {0x0948};
static const unsigned long cp_single_1049[] = {0x0ac8};
static const unsigned long cp_single_1050[] = {0x30a2};
static const unsigned long cp_single_1051[] = {0xff71};
static const unsigned long cp_single_1052[] = {0x314f};
static const unsigned long cp_single_1053[] = {0x05d0};
static const unsigned long cp_single_1054[] = {0x0627};
static const unsigned long cp_single_1055[] = {0xfb30};
static const unsigned long cp_single_1056[] = {0xfe8e};
static const unsigned long cp_single_1057[] = {0x0623};
static const unsigned long cp_single_1058[] = {0xfe84};
static const unsigned long cp_single_1059[] = {0x0625};
static const unsigned long cp_single_1060[] = {0xfe88};
static const unsigned long cp_single_1061[] = {0x05d0};
static const unsigned long cp_single_1062[] = {0xfb4f};
static const unsigned long cp_single_1063[] = {0x0622};
static const unsigned long cp_single_1064[] = {0xfe82};
static const unsigned long cp_single_1065[] = {0x0649};
static const unsigned long cp_single_1066[] = {0xfef0};
static const unsigned long cp_single_1067[] = {0xfef3};
static const unsigned long cp_single_1068[] = {0xfef4};
static const unsigned long cp_single_1069[] = {0xfb2e};
static const unsigned long cp_single_1070[] = {0xfb2f};
static const unsigned long cp_single_1071[] = {0x2135};
static const unsigned long cp_single_1072[] = {0x224c};
static const unsigned long cp_single_1073[] = {0x03b1};
static const unsigned long cp_single_1074[] = {0x03ac};
static const unsigned long cp_single_1075[] = {0x0101};
static const unsigned long cp_single_1076[] = {0xff41};
static const unsigned long cp_single_1077[] = {0x0026};
static const unsigned long cp_single_1078[] = {0xff06};
static const unsigned long cp_single_1079[] = {0xf726};
static const unsigned long cp_single_1080[] = {0x33c2};
static const unsigned long cp_single_1081[] = {0x3122};
static const unsigned long cp_single_1082[] = {0x3124};
static const unsigned long cp_single_1083[] = {0x0e5a};
static const unsigned long cp_single_1084[] = {0x2220};
static const unsigned long cp_single_1085[] = {0x3008};
static const unsigned long cp_single_1086[] = {0xfe3f};
static const unsigned long cp_single_1087[] = {0x3009};
static const unsigned long cp_single_1088[] = {0xfe40};
static const unsigned long cp_single_1089[] = {0x2329};
static const unsigned long cp_single_1090[] = {0x232a};
static const unsigned long cp_single_1091[] = {0x212b};
static const unsigned long cp_single_1092[] = {0x0387};
static const unsigned long cp_single_1093[] = {0x0952};
static const unsigned long cp_single_1094[] = {0x0982};
static const unsigned long cp_single_1095[] = {0x0902};
static const unsigned long cp_single_1096[] = {0x0a82};
static const unsigned long cp_single_1097[] = {0x0105};
static const unsigned long cp_single_1098[] = {0x3300};
static const unsigned long cp_single_1099[] = {0x249c};
static const unsigned long cp_single_1100[] = {0x055a};
static const unsigned long cp_single_1101[] = {0x02bc};
static const unsigned long cp_single_1102[] = {0xf8ff};
static const unsigned long cp_single_1103[] = {0x2250};
static const unsigned long cp_single_1104[] = {0x2248};
static const unsigned long cp_single_1105[] = {0x2252};
static const unsigned long cp_single_1106[] = {0x2245};
static const unsigned long cp_single_1107[] = {0x318e};
static const unsigned long cp_single_1108[] = {0x318d};
static const unsigned long cp_single_1109[] = {0x2312};
static const unsigned long cp_single_1110[] = {0x1e9a};
static const unsigned long cp_single_1111[] = {0x00e5};
static const unsigned long cp_single_1112[] = {0x01fb};
static const unsigned long cp_single_1113[] = {0x1e01};
static const unsigned long cp_single_1114[] = {0x2194};
static const unsigned long cp_single_1115[] = {0x21e3};
static const unsigned long cp_single_1116[] = {0x21e0};
static const unsigned long cp_single_1117[] = {0x21e2};
static const unsigned long cp_single_1118[] = {0x21e1};
static const unsigned long cp_single_1119[] = {0x21d4};
static const unsigned long cp_single_1120[] = {0x21d3};
static const unsigned long cp_single_1121[] = {0x21d0};
static const unsigned long cp_single_1122[] = {0x21d2};
static const unsigned long cp_single_1123[] = {0x21d1};
static const unsigned long cp_single_1124[] = {0x2193};
static const unsigned long cp_single_1125[] = {0x2199};
static const unsigned long cp_single_1126[] = {0x2198};
static const unsigned long cp_single_1127[] = {0x21e9};
static const unsigned long cp_single_1128[] = {0x02c5};
static const unsigned long cp_single_1129[] = {0x02c2};
static const unsigned long cp_single_1130[] = {0x02c3};
static const unsigned long cp_single_1131[] = {0x02c4};
static const unsigned long cp_single_1132[] = {0xf8e7};
static const unsigned long cp_single_1133[] = {0x2190};
static const unsigned long cp_single_1134[] = {0x21d0};
static const unsigned long cp_single_1135[] = {0x21cd};
static const unsigned long cp_single_1136[] = {0x21c6};
static const unsigned long cp_single_1137[] = {0x21e6};
static const unsigned long cp_single_1138[] = {0x2192};
static const unsigned long cp_single_1139[] = {0x21cf};
static const unsigned long cp_single_1140[] = {0x279e};
static const unsigned long cp_single_1141[] = {0x21c4};
static const unsigned long cp_single_1142[] = {0x21e8};
static const unsigned long cp_single_1143[] = {0x21e4};
static const unsigned long cp_single_1144[] = {0x21e5};
static const unsigned long cp_single_1145[] = {0x2191};
static const unsigned long cp_single_1146[] = {0x2195};
static const unsigned long cp_single_1147[] = {0x21a8};
static const unsigned long cp_single_1148[] = {0x21a8};
static const unsigned long cp_single_1149[] = {0x2196};
static const unsigned long cp_single_1150[] = {0x21c5};
static const unsigned long cp_single_1151[] = {0x2197};
static const unsigned long cp_single_1152[] = {0x21e7};
static const unsigned long cp_single_1153[] = {0xf8e6};
static const unsigned long cp_single_1154[] = {0x005e};
static const unsigned long cp_single_1155[] = {0xff3e};
static const unsigned long cp_single_1156[] = {0x007e};
static const unsigned long cp_single_1157[] = {0xff5e};
static const unsigned long cp_single_1158[] = {0x0251};
static const unsigned long cp_single_1159[] = {0x0252};
static const unsigned long cp_single_1160[] = {0x3041};
static const unsigned long cp_single_1161[] = {0x30a1};
static const unsigned long cp_single_1162[] = {0xff67};
static const unsigned long cp_single_1163[] = {0x002a};
static const unsigned long cp_single_1164[] = {0x066d};
static const unsigned long cp_single_1165[] = {0x066d};
static const unsigned long cp_single_1166[] = {0x2217};
static const unsigned long cp_single_1167[] = {0xff0a};
static const unsigned long cp_single_1168[] = {0xfe61};
static const unsigned long cp_single_1169[] = {0x2042};
static const unsigned long cp_single_1170[] = {0xf6e9};
static const unsigned long cp_single_1171[] = {0x2243};
static const unsigned long cp_single_1172[] = {0x0040};
static const unsigned long cp_single_1173[] = {0x00e3};
static const unsigned long cp_single_1174[] = {0xff20};
static const unsigned long cp_single_1175[] = {0xfe6b};
static const unsigned long cp_single_1176[] = {0x0250};
static const unsigned long cp_single_1177[] = {0x0994};
static const unsigned long cp_single_1178[] = {0x3120};
static const unsigned long cp_single_1179[] = {0x0914};
static const unsigned long cp_single_1180[] = {0x0a94};
static const unsigned long cp_single_1181[] = {0x0a14};
static const unsigned long cp_single_1182[] = {0x09d7};
static const unsigned long cp_single_1183[] = {0x0a4c};
static const unsigned long cp_single_1184[] = {0x09cc};
static const unsigned long cp_single_1185[] = {0x094c};
static const unsigned long cp_single_1186[] = {0x0acc};
static const unsigned long cp_single_1187[] = {0x093d};
static const unsigned long cp_single_1188[] = {0x0561};
static const unsigned long cp_single_1189[] = {0x05e2};
static const unsigned long cp_single_1190[] = {0xfb20};
static const unsigned long cp_single_1191[] = {0x05e2};
static const unsigned long cp_single_1192[] = {0x0062};
static const unsigned long cp_single_1193[] = {0x09ac};
static const unsigned long cp_single_1194[] = {0x005c};
static const unsigned long cp_single_1195[] = {0xff3c};
static const unsigned long cp_single_1196[] = {0x092c};
static const unsigned long cp_single_1197[] = {0x0aac};
static const unsigned long cp_single_1198[] = {0x0a2c};
static const unsigned long cp_single_1199[] = {0x3070};
static const unsigned long cp_single_1200[] = {0x0e3f};
static const unsigned long cp_single_1201[] = {0x30d0};
static const unsigned long cp_single_1202[] = {0x007c};
static const unsigned long cp_single_1203[] = {0xff5c};
static const unsigned long cp_single_1204[] = {0x3105};
static const unsigned long cp_single_1205[] = {0x24d1};
static const unsigned long cp_single_1206[] = {0x1e03};
static const unsigned long cp_single_1207[] = {0x1e05};
static const unsigned long cp_single_1208[] = {0x266c};
static const unsigned long cp_single_1209[] = {0x2235};
static const unsigned long cp_single_1210[] = {0x0431};
static const unsigned long cp_single_1211[] = {0x0628};
static const unsigned long cp_single_1212[] = {0xfe90};
static const unsigned long cp_single_1213[] = {0xfe91};
static const unsigned long cp_single_1214[] = {0x3079};
static const unsigned long cp_single_1215[] = {0xfe92};
static const unsigned long cp_single_1216[] = {0xfc9f};
static const unsigned long cp_single_1217[] = {0xfc08};
static const unsigned long cp_single_1218[] = {0xfc6d};
static const unsigned long cp_single_1219[] = {0x30d9};
static const unsigned long cp_single_1220[] = {0x0562};
static const unsigned long cp_single_1221[] = {0x05d1};
static const unsigned long cp_single_1222[] = {0x03b2};
static const unsigned long cp_single_1223[] = {0x03d0};
static const unsigned long cp_single_1224[] = {0xfb31};
static const unsigned long cp_single_1225[] = {0xfb31};
static const unsigned long cp_single_1226[] = {0x05d1};
static const unsigned long cp_single_1227[] = {0xfb4c};
static const unsigned long cp_single_1228[] = {0x09ad};
static const unsigned long cp_single_1229[] = {0x092d};
static const unsigned long cp_single_1230[] = {0x0aad};
static const unsigned long cp_single_1231[] = {0x0a2d};
static const unsigned long cp_single_1232[] = {0x0253};
static const unsigned long cp_single_1233[] = {0x3073};
static const unsigned long cp_single_1234[] = {0x30d3};
static const unsigned long cp_single_1235[] = {0x0298};
static const unsigned long cp_single_1236[] = {0x0a02};
static const unsigned long cp_single_1237[] = {0x3331};
static const unsigned long cp_single_1238[] = {0x25cf};
static const unsigned long cp_single_1239[] = {0x25c6};
static const unsigned long cp_single_1240[] = {0x25bc};
static const unsigned long cp_single_1241[] = {0x25c4};
static const unsigned long cp_single_1242[] = {0x25c0};
static const unsigned long cp_single_1243[] = {0x3010};
static const unsigned long cp_single_1244[] = {0xfe3b};
static const unsigned long cp_single_1245[] = {0x3011};
static const unsigned long cp_single_1246[] = {0xfe3c};
static const unsigned long cp_single_1247[] = {0x25e3};
static const unsigned long cp_single_1248[] = {0x25e2};
static const unsigned long cp_single_1249[] = {0x25ac};
static const unsigned long cp_single_1250[] = {0x25ba};
static const unsigned long cp_single_1251[] = {0x25b6};
static const unsigned long cp_single_1252[] = {0x25aa};
static const unsigned long cp_single_1253[] = {0x263b};
static const unsigned long cp_single_1254[] = {0x25a0};
static const unsigned long cp_single_1255[] = {0x2605};
static const unsigned long cp_single_1256[] = {0x25e4};
static const unsigned long cp_single_1257[] = {0x25e5};
static const unsigned long cp_single_1258[] = {0x25b4};
static const unsigned long cp_single_1259[] = {0x25b2};
static const unsigned long cp_single_1260[] = {0x2423};
static const unsigned long cp_single_1261[] = {0x1e07};
static const unsigned long cp_single_1262[] = {0x2588};
static const unsigned long cp_single_1263[] = {0xff42};
static const unsigned long cp_single_1264[] = {0x0e1a};
static const unsigned long cp_single_1265[] = {0x307c};
static const unsigned long cp_single_1266[] = {0x30dc};
static const unsigned long cp_single_1267[] = {0x249d};
static const unsigned long cp_single_1268[] = {0x33c3};
static const unsigned long cp_single_1269[] = {0xf8f4};
static const unsigned long cp_single_1270[] = {0x007b};
static const unsigned long cp_single_1271[] = {0xf8f3};
static const unsigned long cp_single_1272[] = {0xf8f2};
static const unsigned long cp_single_1273[] = {0xff5b};
static const unsigned long cp_single_1274[] = {0xfe5b};
static const unsigned long cp_single_1275[] = {0xf8f1};
static const unsigned long cp_single_1276[] = {0xfe37};
static const unsigned long cp_single_1277[] = {0x007d};
static const unsigned long cp_single_1278[] = {0xf8fe};
static const unsigned long cp_single_1279[] = {0xf8fd};
static const unsigned long cp_single_1280[] = {0xff5d};
static const unsigned long cp_single_1281[] = {0xfe5c};
static const unsigned long cp_single_1282[] = {0xf8fc};
static const unsigned long cp_single_1283[] = {0xfe38};
static const unsigned long cp_single_1284[] = {0x005b};
static const unsigned long cp_single_1285[] = {0xf8f0};
static const unsigned long cp_single_1286[] = {0xf8ef};
static const unsigned long cp_single_1287[] = {0xff3b};
static const unsigned long cp_single_1288[] = {0xf8ee};
static const unsigned long cp_single_1289[] = {0x005d};
static const unsigned long cp_single_1290[] = {0xf8fb};
static const unsigned long cp_single_1291[] = {0xf8fa};
static const unsigned long cp_single_1292[] = {0xff3d};
static const unsigned long cp_single_1293[] = {0xf8f9};
static const unsigned long cp_single_1294[] = {0x02d8};
static const unsigned long cp_single_1295[] = {0x032e};
static const unsigned long cp_single_1296[] = {0x0306};
static const unsigned long cp_single_1297[] = {0x032f};
static const unsigned long cp_single_1298[] = {0x0311};
static const unsigned long cp_single_1299[] = {0x0361};
static const unsigned long cp_single_1300[] = {0x032a};
static const unsigned long cp_single_1301[] = {0x033a};
static const unsigned long cp_single_1302[] = {0x00a6};
static const unsigned long cp_single_1303[] = {0x0180};
static const unsigned long cp_single_1304[] = {0xf6ea};
static const unsigned long cp_single_1305[] = {0x0183};
static const unsigned long cp_single_1306[] = {0x3076};
static const unsigned long cp_single_1307[] = {0x30d6};
static const unsigned long cp_single_1308[] = {0x2022};
static const unsigned long cp_single_1309[] = {0x25d8};
static const unsigned long cp_single_1310[] = {0x2219};
static const unsigned long cp_single_1311[] = {0x25ce};
static const unsigned long cp_single_1312[] = {0x0063};
static const unsigned long cp_single_1313[] = {0x056e};
static const unsigned long cp_single_1314[] = {0x099a};
static const unsigned long cp_single_1315[] = {0x0107};
static const unsigned long cp_single_1316[] = {0x091a};
static const unsigned long cp_single_1317[] = {0x0a9a};
static const unsigned long cp_single_1318[] = {0x0a1a};
static const unsigned long cp_single_1319[] = {0x3388};
static const unsigned long cp_single_1320[] = {0x0981};
static const unsigned long cp_single_1321[] = {0x0310};
static const unsigned long cp_single_1322[] = {0x0901};
static const unsigned long cp_single_1323[] = {0x0a81};
static const unsigned long cp_single_1324[] = {0x21ea};
static const unsigned long cp_single_1325[] = {0x2105};
static const unsigned long cp_single_1326[] = {0x02c7};
static const unsigned long cp_single_1327[] = {0x032c};
static const unsigned long cp_single_1328[] = {0x030c};
static const unsigned long cp_single_1329[] = {0x21b5};
static const unsigned long cp_single_1330[] = {0x3118};
static const unsigned long cp_single_1331[] = {0x010d};
static const unsigned long cp_single_1332[] = {0x00e7};
static const unsigned long cp_single_1333[] = {0x1e09};
static const unsigned long cp_single_1334[] = {0x24d2};
static const unsigned long cp_single_1335[] = {0x0109};
static const unsigned long cp_single_1336[] = {0x0255};
static const unsigned long cp_single_1337[] = {0x010b};
static const unsigned long cp_single_1338[] = {0x010b};
static const unsigned long cp_single_1339[] = {0x33c5};
static const unsigned long cp_single_1340[] = {0x00b8};
static const unsigned long cp_single_1341[] = {0x0327};
static const unsigned long cp_single_1342[] = {0x00a2};
static const unsigned long cp_single_1343[] = {0x2103};
static const unsigned long cp_single_1344[] = {0xf6df};
static const unsigned long cp_single_1345[] = {0xffe0};
static const unsigned long cp_single_1346[] = {0xf7a2};
static const unsigned long cp_single_1347[] = {0xf6e0};
static const unsigned long cp_single_1348[] = {0x0579};
static const unsigned long cp_single_1349[] = {0x099b};
static const unsigned long cp_single_1350[] = {0x091b};
static const unsigned long cp_single_1351[] = {0x0a9b};
static const unsigned long cp_single_1352[] = {0x0a1b};
static const unsigned long cp_single_1353[] = {0x3114};
static const unsigned long cp_single_1354[] = {0x04bd};
static const unsigned long cp_single_1355[] = {0x2713};
static const unsigned long cp_single_1356[] = {0x0447};
static const unsigned long cp_single_1357[] = {0x04bf};
static const unsigned long cp_single_1358[] = {0x04b7};
static const unsigned long cp_single_1359[] = {0x04f5};
static const unsigned long cp_single_1360[] = {0x0573};
static const unsigned long cp_single_1361[] = {0x04cc};
static const unsigned long cp_single_1362[] = {0x04b9};
static const unsigned long cp_single_1363[] = {0x03c7};
static const unsigned long cp_single_1364[] = {0x3277};
static const unsigned long cp_single_1365[] = {0x3217};
static const unsigned long cp_single_1366[] = {0x3269};
static const unsigned long cp_single_1367[] = {0x314a};
static const unsigned long cp_single_1368[] = {0x3209};
static const unsigned long cp_single_1369[] = {0x0e0a};
static const unsigned long cp_single_1370[] = {0x0e08};
static const unsigned long cp_single_1371[] = {0x0e09};
static const unsigned long cp_single_1372[] = {0x0e0c};
static const unsigned long cp_single_1373[] = {0x0188};
static const unsigned long cp_single_1374[] = {0x3276};
static const unsigned long cp_single_1375[] = {0x3216};
static const unsigned long cp_single_1376[] = {0x3268};
static const unsigned long cp_single_1377[] = {0x3148};
static const unsigned long cp_single_1378[] = {0x3208};
static const unsigned long cp_single_1379[] = {0x321c};
static const unsigned long cp_single_1380[] = {0x25cb};
static const unsigned long cp_single_1381[] = {0x2297};
static const unsigned long cp_single_1382[] = {0x2299};
static const unsigned long cp_single_1383[] = {0x2295};
static const unsigned long cp_single_1384[] = {0x3036};
static const unsigned long cp_single_1385[] = {0x25d0};
static const unsigned long cp_single_1386[] = {0x25d1};
static const unsigned long cp_single_1387[] = {0x02c6};
static const unsigned long cp_single_1388[] = {0x032d};
static const unsigned long cp_single_1389[] = {0x0302};
static const unsigned long cp_single_1390[] = {0x2327};
static const unsigned long cp_single_1391[] = {0x01c2};
static const unsigned long cp_single_1392[] = {0x01c0};
static const unsigned long cp_single_1393[] = {0x01c1};
static const unsigned long cp_single_1394[] = {0x01c3};
static const unsigned long cp_single_1395[] = {0x2663};
static const unsigned long cp_single_1396[] = {0x2663};
static const unsigned long cp_single_1397[] = {0x2667};
static const unsigned long cp_single_1398[] = {0x33a4};
static const unsigned long cp_single_1399[] = {0xff43};
static const unsigned long cp_single_1400[] = {0x33a0};
static const unsigned long cp_single_1401[] = {0x0581};
static const unsigned long cp_single_1402[] = {0x003a};
static const unsigned long cp_single_1403[] = {0x20a1};
static const unsigned long cp_single_1404[] = {0xff1a};
static const unsigned long cp_single_1405[] = {0x20a1};
static const unsigned long cp_single_1406[] = {0xfe55};
static const unsigned long cp_single_1407[] = {0x02d1};
static const unsigned long cp_single_1408[] = {0x02d0};
static const unsigned long cp_single_1409[] = {0x002c};
static const unsigned long cp_single_1410[] = {0x0313};
static const unsigned long cp_single_1411[] = {0x0315};
static const unsigned long cp_single_1412[] = {0xf6c3};
static const unsigned long cp_single_1413[] = {0x060c};
static const unsigned long cp_single_1414[] = {0x055d};
static const unsigned long cp_single_1415[] = {0xf6e1};
static const unsigned long cp_single_1416[] = {0xff0c};
static const unsigned long cp_single_1417[] = {0x0314};
static const unsigned long cp_single_1418[] = {0x02bd};
static const unsigned long cp_single_1419[] = {0xfe50};
static const unsigned long cp_single_1420[] = {0xf6e2};
static const unsigned long cp_single_1421[] = {0x0312};
static const unsigned long cp_single_1422[] = {0x02bb};
static const unsigned long cp_single_1423[] = {0x263c};
static const unsigned long cp_single_1424[] = {0x2245};
static const unsigned long cp_single_1425[] = {0x222e};
static const unsigned long cp_single_1426[] = {0x2303};
static const unsigned long cp_single_1427[] = {0x0006};
static const unsigned long cp_single_1428[] = {0x0007};
static const unsigned long cp_single_1429[] = {0x0008};
static const unsigned long cp_single_1430[] = {0x0018};
static const unsigned long cp_single_1431[] = {0x000d};
static const unsigned long cp_single_1432[] = {0x0011};
static const unsigned long cp_single_1433[] = {0x0012};
static const unsigned long cp_single_1434[] = {0x0013};
static const unsigned long cp_single_1435[] = {0x0014};
static const unsigned long cp_single_1436[] = {0x007f};
static const unsigned long cp_single_1437[] = {0x0010};
static const unsigned long cp_single_1438[] = {0x0019};
static const unsigned long cp_single_1439[] = {0x0005};
static const unsigned long cp_single_1440[] = {0x0004};
static const unsigned long cp_single_1441[] = {0x001b};
static const unsigned long cp_single_1442[] = {0x0017};
static const unsigned long cp_single_1443[] = {0x0003};
static const unsigned long cp_single_1444[] = {0x000c};
static const unsigned long cp_single_1445[] = {0x001c};
static const unsigned long cp_single_1446[] = {0x001d};
static const unsigned long cp_single_1447[] = {0x0009};
static const unsigned long cp_single_1448[] = {0x000a};
static const unsigned long cp_single_1449[] = {0x0015};
static const unsigned long cp_single_1450[] = {0x001e};
static const unsigned long cp_single_1451[] = {0x000f};
static const unsigned long cp_single_1452[] = {0x000e};
static const unsigned long cp_single_1453[] = {0x0002};
static const unsigned long cp_single_1454[] = {0x0001};
static const unsigned long cp_single_1455[] = {0x001a};
static const unsigned long cp_single_1456[] = {0x0016};
static const unsigned long cp_single_1457[] = {0x001f};
static const unsigned long cp_single_1458[] = {0x000b};
static const unsigned long cp_single_1459[] = {0x00a9};
static const unsigned long cp_single_1460[] = {0xf8e9};
static const unsigned long cp_single_1461[] = {0xf6d9};
static const unsigned long cp_single_1462[] = {0x300c};
static const unsigned long cp_single_1463[] = {0xff62};
static const unsigned long cp_single_1464[] = {0xfe41};
static const unsigned long cp_single_1465[] = {0x300d};
static const unsigned long cp_single_1466[] = {0xff63};
static const unsigned long cp_single_1467[] = {0xfe42};
static const unsigned long cp_single_1468[] = {0x337f};
static const unsigned long cp_single_1469[] = {0x33c7};
static const unsigned long cp_single_1470[] = {0x33c6};
static const unsigned long cp_single_1471[] = {0x249e};
static const unsigned long cp_single_1472[] = {0x20a2};
static const unsigned long cp_single_1473[] = {0x0297};
static const unsigned long cp_single_1474[] = {0x22cf};
static const unsigned long cp_single_1475[] = {0x22ce};
static const unsigned long cp_single_1476[] = {0x00a4};
static const unsigned long cp_single_1477[] = {0xf6d1};
static const unsigned long cp_single_1478[] = {0xf6d2};
static const unsigned long cp_single_1479[] = {0xf6d4};
static const unsigned long cp_single_1480[] = {0xf6d5};
static const unsigned long cp_single_1481[] = {0x0064};
static const unsigned long cp_single_1482[] = {0x0564};
static const unsigned long cp_single_1483[] = {0x09a6};
static const unsigned long cp_single_1484[] = {0x0636};
static const unsigned long cp_single_1485[] = {0x0926};
static const unsigned long cp_single_1486[] = {0xfebe};
static const unsigned long cp_single_1487[] = {0xfebf};
static const unsigned long cp_single_1488[] = {0xfec0};
static const unsigned long cp_single_1489[] = {0x05bc};
static const unsigned long cp_single_1490[] = {0x05bc};
static const unsigned long cp_single_1491[] = {0x2020};
static const unsigned long cp_single_1492[] = {0x2021};
static const unsigned long cp_single_1493[] = {0x0aa6};
static const unsigned long cp_single_1494[] = {0x0a26};
static const unsigned long cp_single_1495[] = {0x3060};
static const unsigned long cp_single_1496[] = {0x30c0};
static const unsigned long cp_single_1497[] = {0x062f};
static const unsigned long cp_single_1498[] = {0x05d3};
static const unsigned long cp_single_1499[] = {0xfb33};
static const unsigned long cp_single_1500[] = {0xfb33};
static const unsigned long cp_single_1501[] = {0x05d3};
static const unsigned long cp_single_1502[] = {0xfeaa};
static const unsigned long cp_single_1503[] = {0x064f};
static const unsigned long cp_single_1504[] = {0x064f};
static const unsigned long cp_single_1505[] = {0x064c};
static const unsigned long cp_single_1506[] = {0x064c};
static const unsigned long cp_single_1507[] = {0x0964};
static const unsigned long cp_single_1508[] = {0x05a7};
static const unsigned long cp_single_1509[] = {0x05a7};
static const unsigned long cp_single_1510[] = {0x0485};
static const unsigned long cp_single_1511[] = {0xf6d3};
static const unsigned long cp_single_1512[] = {0x300a};
static const unsigned long cp_single_1513[] = {0xfe3d};
static const unsigned long cp_single_1514[] = {0x300b};
static const unsigned long cp_single_1515[] = {0xfe3e};
static const unsigned long cp_single_1516[] = {0x032b};
static const unsigned long cp_single_1517[] = {0x21d4};
static const unsigned long cp_single_1518[] = {0x21d2};
static const unsigned long cp_single_1519[] = {0x0965};
static const unsigned long cp_single_1520[] = {0xf6d6};
static const unsigned long cp_single_1521[] = {0x030f};
static const unsigned long cp_single_1522[] = {0x222c};
static const unsigned long cp_single_1523[] = {0x2017};
static const unsigned long cp_single_1524[] = {0x0333};
static const unsigned long cp_single_1525[] = {0x033f};
static const unsigned long cp_single_1526[] = {0x02ba};
static const unsigned long cp_single_1527[] = {0x2016};
static const unsigned long cp_single_1528[] = {0x030e};
static const unsigned long cp_single_1529[] = {0x3109};
static const unsigned long cp_single_1530[] = {0x33c8};
static const unsigned long cp_single_1531[] = {0x010f};
static const unsigned long cp_single_1532[] = {0x1e11};
static const unsigned long cp_single_1533[] = {0x24d3};
static const unsigned long cp_single_1534[] = {0x1e13};
static const unsigned long cp_single_1535[] = {0x0111};
static const unsigned long cp_single_1536[] = {0x09a1};
static const unsigned long cp_single_1537[] = {0x0921};
static const unsigned long cp_single_1538[] = {0x0aa1};
static const unsigned long cp_single_1539[] = {0x0a21};
static const unsigned long cp_single_1540[] = {0x0688};
static const unsigned long cp_single_1541[] = {0xfb89};
static const unsigned long cp_single_1542[] = {0x095c};
static const unsigned long cp_single_1543[] = {0x09a2};
static const unsigned long cp_single_1544[] = {0x0922};
static const unsigned long cp_single_1545[] = {0x0aa2};
static const unsigned long cp_single_1546[] = {0x0a22};
static const unsigned long cp_single_1547[] = {0x1e0b};
static const unsigned long cp_single_1548[] = {0x1e0d};
static const unsigned long cp_single_1549[] = {0x066b};
static const unsigned long cp_single_1550[] = {0x066b};
static const unsigned long cp_single_1551[] = {0x0434};
static const unsigned long cp_single_1552[] = {0x00b0};
static const unsigned long cp_single_1553[] = {0x05ad};
static const unsigned long cp_single_1554[] = {0x3067};
static const unsigned long cp_single_1555[] = {0x03ef};
static const unsigned long cp_single_1556[] = {0x30c7};
static const unsigned long cp_single_1557[] = {0x232b};
static const unsigned long cp_single_1558[] = {0x2326};
static const unsigned long cp_single_1559[] = {0x03b4};
static const unsigned long cp_single_1560[] = {0x018d};
static const unsigned long cp_single_1561[] = {0x09f8};
static const unsigned long cp_single_1562[] = {0x02a4};
static const unsigned long cp_single_1563[] = {0x09a7};
static const unsigned long cp_single_1564[] = {0x0927};
static const unsigned long cp_single_1565[] = {0x0aa7};
static const unsigned long cp_single_1566[] = {0x0a27};
static const unsigned long cp_single_1567[] = {0x0257};
static const unsigned long cp_single_1568[] = {0x0385};
static const unsigned long cp_single_1569[] = {0x0344};
static const unsigned long cp_single_1570[] = {0x2666};
static const unsigned long cp_single_1571[] = {0x2662};
static const unsigned long cp_single_1572[] = {0x00a8};
static const unsigned long cp_single_1573[] = {0xf6d7};
static const unsigned long cp_single_1574[] = {0x0324};
static const unsigned long cp_single_1575[] = {0x0308};
static const unsigned long cp_single_1576[] = {0xf6d8};
static const unsigned long cp_single_1577[] = {0x0385};
static const unsigned long cp_single_1578[] = {0x3062};
static const unsigned long cp_single_1579[] = {0x30c2};
static const unsigned long cp_single_1580[] = {0x3003};
static const unsigned long cp_single_1581[] = {0x00f7};
static const unsigned long cp_single_1582[] = {0x2223};
static const unsigned long cp_single_1583[] = {0x2215};
static const unsigned long cp_single_1584[] = {0x0452};
static const unsigned long cp_single_1585[] = {0x2593};
static const unsigned long cp_single_1586[] = {0x1e0f};
static const unsigned long cp_single_1587[] = {0x3397};
static const unsigned long cp_single_1588[] = {0x0111};
static const unsigned long cp_single_1589[] = {0xff44};
static const unsigned long cp_single_1590[] = {0x2584};
static const unsigned long cp_single_1591[] = {0x0e0e};
static const unsigned long cp_single_1592[] = {0x0e14};
static const unsigned long cp_single_1593[] = {0x3069};
static const unsigned long cp_single_1594[] = {0x30c9};
static const unsigned long cp_single_1595[] = {0x0024};
static const unsigned long cp_single_1596[] = {0xf6e3};
static const unsigned long cp_single_1597[] = {0xff04};
static const unsigned long cp_single_1598[] = {0xf724};
static const unsigned long cp_single_1599[] = {0xfe69};
static const unsigned long cp_single_1600[] = {0xf6e4};
static const unsigned long cp_single_1601[] = {0x20ab};
static const unsigned long cp_single_1602[] = {0x3326};
static const unsigned long cp_single_1603[] = {0x02d9};
static const unsigned long cp_single_1604[] = {0x0307};
static const unsigned long cp_single_1605[] = {0x0323};
static const unsigned long cp_single_1606[] = {0x0323};
static const unsigned long cp_single_1607[] = {0x30fb};
static const unsigned long cp_single_1608[] = {0x0131};
static const unsigned long cp_single_1609[] = {0xf6be};
static const unsigned long cp_single_1610[] = {0x0284};
static const unsigned long cp_single_1611[] = {0x22c5};
static const unsigned long cp_single_1612[] = {0x25cc};
static const unsigned long cp_single_1613[] = {0xfb1f};
static const unsigned long cp_single_1614[] = {0xfb1f};
static const unsigned long cp_single_1615[] = {0x031e};
static const unsigned long cp_single_1616[] = {0x02d5};
static const unsigned long cp_single_1617[] = {0x249f};
static const unsigned long cp_single_1618[] = {0xf6eb};
static const unsigned long cp_single_1619[] = {0x0256};
static const unsigned long cp_single_1620[] = {0x018c};
static const unsigned long cp_single_1621[] = {0x3065};
static const unsigned long cp_single_1622[] = {0x30c5};
static const unsigned long cp_single_1623[] = {0x01f3};
static const unsigned long cp_single_1624[] = {0x02a3};
static const unsigned long cp_single_1625[] = {0x01c6};
static const unsigned long cp_single_1626[] = {0x02a5};
static const unsigned long cp_single_1627[] = {0x04e1};
static const unsigned long cp_single_1628[] = {0x0455};
static const unsigned long cp_single_1629[] = {0x045f};
static const unsigned long cp_single_1630[] = {0x0065};
static const unsigned long cp_single_1631[] = {0x00e9};
static const unsigned long cp_single_1632[] = {0x2641};
static const unsigned long cp_single_1633[] = {0x098f};
static const unsigned long cp_single_1634[] = {0x311c};
static const unsigned long cp_single_1635[] = {0x0115};
static const unsigned long cp_single_1636[] = {0x090d};
static const unsigned long cp_single_1637[] = {0x0a8d};
static const unsigned long cp_single_1638[] = {0x0945};
static const unsigned long cp_single_1639[] = {0x0ac5};
static const unsigned long cp_single_1640[] = {0x011b};
static const unsigned long cp_single_1641[] = {0x1e1d};
static const unsigned long cp_single_1642[] = {0x0565};
static const unsigned long cp_single_1643[] = {0x0587};
static const unsigned long cp_single_1644[] = {0x24d4};
static const unsigned long cp_single_1645[] = {0x00ea};
static const unsigned long cp_single_1646[] = {0x1ebf};
static const unsigned long cp_single_1647[] = {0x1e19};
static const unsigned long cp_single_1648[] = {0x1ec7};
static const unsigned long cp_single_1649[] = {0x1ec1};
static const unsigned long cp_single_1650[] = {0x1ec3};
static const unsigned long cp_single_1651[] = {0x1ec5};
static const unsigned long cp_single_1652[] = {0x0454};
static const unsigned long cp_single_1653[] = {0x0205};
static const unsigned long cp_single_1654[] = {0x090f};
static const unsigned long cp_single_1655[] = {0x00eb};
static const unsigned long cp_single_1656[] = {0x0117};
static const unsigned long cp_single_1657[] = {0x0117};
static const unsigned long cp_single_1658[] = {0x1eb9};
static const unsigned long cp_single_1659[] = {0x0a0f};
static const unsigned long cp_single_1660[] = {0x0a47};
static const unsigned long cp_single_1661[] = {0x0444};
static const unsigned long cp_single_1662[] = {0x00e8};
static const unsigned long cp_single_1663[] = {0x0a8f};
static const unsigned long cp_single_1664[] = {0x0567};
static const unsigned long cp_single_1665[] = {0x311d};
static const unsigned long cp_single_1666[] = {0x3048};
static const unsigned long cp_single_1667[] = {0x1ebb};
static const unsigned long cp_single_1668[] = {0x311f};
static const unsigned long cp_single_1669[] = {0x0038};
static const unsigned long cp_single_1670[] = {0x0668};
static const unsigned long cp_single_1671[] = {0x09ee};
static const unsigned long cp_single_1672[] = {0x2467};
static const unsigned long cp_single_1673[] = {0x2791};
static const unsigned long cp_single_1674[] = {0x096e};
static const unsigned long cp_single_1675[] = {0x2471};
static const unsigned long cp_single_1676[] = {0x2485};
static const unsigned long cp_single_1677[] = {0x2499};
static const unsigned long cp_single_1678[] = {0x0aee};
static const unsigned long cp_single_1679[] = {0x0a6e};
static const unsigned long cp_single_1680[] = {0x0668};
static const unsigned long cp_single_1681[] = {0x3028};
static const unsigned long cp_single_1682[] = {0x266b};
static const unsigned long cp_single_1683[] = {0x3227};
static const unsigned long cp_single_1684[] = {0x2088};
static const unsigned long cp_single_1685[] = {0xff18};
static const unsigned long cp_single_1686[] = {0xf738};
static const unsigned long cp_single_1687[] = {0x247b};
static const unsigned long cp_single_1688[] = {0x248f};
static const unsigned long cp_single_1689[] = {0x06f8};
static const unsigned long cp_single_1690[] = {0x2177};
static const unsigned long cp_single_1691[] = {0x2078};
static const unsigned long cp_single_1692[] = {0x0e58};
static const unsigned long cp_single_1693[] = {0x0207};
static const unsigned long cp_single_1694[] = {0x0465};
static const unsigned long cp_single_1695[] = {0x30a8};
static const unsigned long cp_single_1696[] = {0xff74};
static const unsigned long cp_single_1697[] = {0x0a74};
static const unsigned long cp_single_1698[] = {0x3154};
static const unsigned long cp_single_1699[] = {0x043b};
static const unsigned long cp_single_1700[] = {0x2208};
static const unsigned long cp_single_1701[] = {0x246a};
static const unsigned long cp_single_1702[] = {0x247e};
static const unsigned long cp_single_1703[] = {0x2492};
static const unsigned long cp_single_1704[] = {0x217a};
static const unsigned long cp_single_1705[] = {0x2026};
static const unsigned long cp_single_1706[] = {0x22ee};
static const unsigned long cp_single_1707[] = {0x0113};
static const unsigned long cp_single_1708[] = {0x1e17};
static const unsigned long cp_single_1709[] = {0x1e15};
static const unsigned long cp_single_1710[] = {0x043c};
static const unsigned long cp_single_1711[] = {0x2014};
static const unsigned long cp_single_1712[] = {0xfe31};
static const unsigned long cp_single_1713[] = {0xff45};
static const unsigned long cp_single_1714[] = {0x055b};
static const unsigned long cp_single_1715[] = {0x2205};
static const unsigned long cp_single_1716[] = {0x3123};
static const unsigned long cp_single_1717[] = {0x043d};
static const unsigned long cp_single_1718[] = {0x2013};
static const unsigned long cp_single_1719[] = {0xfe32};
static const unsigned long cp_single_1720[] = {0x04a3};
static const unsigned long cp_single_1721[] = {0x014b};
static const unsigned long cp_single_1722[] = {0x3125};
static const unsigned long cp_single_1723[] = {0x04a5};
static const unsigned long cp_single_1724[] = {0x04c8};
static const unsigned long cp_single_1725[] = {0x2002};
static const unsigned long cp_single_1726[] = {0x0119};
static const unsigned long cp_single_1727[] = {0x3153};
static const unsigned long cp_single_1728[] = {0x025b};
static const unsigned long cp_single_1729[] = {0x029a};
static const unsigned long cp_single_1730[] = {0x025c};
static const unsigned long cp_single_1731[] = {0x025e};
static const unsigned long cp_single_1732[] = {0x025d};
static const unsigned long cp_single_1733[] = {0x24a0};
static const unsigned long cp_single_1734[] = {0x03b5};
static const unsigned long cp_single_1735[] = {0x03ad};
static const unsigned long cp_single_1736[] = {0x003d};
static const unsigned long cp_single_1737[] = {0xff1d};
static const unsigned long cp_single_1738[] = {0xfe66};
static const unsigned long cp_single_1739[] = {0x207c};
static const unsigned long cp_single_1740[] = {0x2261};
static const unsigned long cp_single_1741[] = {0x3126};
static const unsigned long cp_single_1742[] = {0x0440};
static const unsigned long cp_single_1743[] = {0x0258};
static const unsigned long cp_single_1744[] = {0x044d};
static const unsigned long cp_single_1745[] = {0x0441};
static const unsigned long cp_single_1746[] = {0x04ab};
static const unsigned long cp_single_1747[] = {0x0283};
static const unsigned long cp_single_1748[] = {0x0286};
static const unsigned long cp_single_1749[] = {0x090e};
static const unsigned long cp_single_1750[] = {0x0946};
static const unsigned long cp_single_1751[] = {0x01aa};
static const unsigned long cp_single_1752[] = {0x0285};
static const unsigned long cp_single_1753[] = {0x3047};
static const unsigned long cp_single_1754[] = {0x30a7};
static const unsigned long cp_single_1755[] = {0xff6a};
static const unsigned long cp_single_1756[] = {0x212e};
static const unsigned long cp_single_1757[] = {0xf6ec};
static const unsigned long cp_single_1758[] = {0x03b7};
static const unsigned long cp_single_1759[] = {0x0568};
static const unsigned long cp_single_1760[] = {0x03ae};
static const unsigned long cp_single_1761[] = {0x00f0};
static const unsigned long cp_single_1762[] = {0x1ebd};
static const unsigned long cp_single_1763[] = {0x1e1b};
static const unsigned long cp_single_1764[] = {0x0591};
static const unsigned long cp_single_1765[] = {0x0591};
static const unsigned long cp_single_1766[] = {0x0591};
static const unsigned long cp_single_1767[] = {0x0591};
static const unsigned long cp_single_1768[] = {0x01dd};
static const unsigned long cp_single_1769[] = {0x3161};
static const unsigned long cp_single_1770[] = {0x20ac};
static const unsigned long cp_single_1771[] = {0x09c7};
static const unsigned long cp_single_1772[] = {0x0947};
static const unsigned long cp_single_1773[] = {0x0ac7};
static const unsigned long cp_single_1774[] = {0x0021};
static const unsigned long cp_single_1775[] = {0x055c};
static const unsigned long cp_single_1776[] = {0x203c};
static const unsigned long cp_single_1777[] = {0x00a1};
static const unsigned long cp_single_1778[] = {0xf7a1};
static const unsigned long cp_single_1779[] = {0xff01};
static const unsigned long cp_single_1780[] = {0xf721};
static const unsigned long cp_single_1781[] = {0x2203};
static const unsigned long cp_single_1782[] = {0x0292};
static const unsigned long cp_single_1783[] = {0x01ef};
static const unsigned long cp_single_1784[] = {0x0293};
static const unsigned long cp_single_1785[] = {0x01b9};
static const unsigned long cp_single_1786[] = {0x01ba};
static const unsigned long cp_single_1787[] = {0x0066};
static const unsigned long cp_single_1788[] = {0x095e};
static const unsigned long cp_single_1789[] = {0x0a5e};
static const unsigned long cp_single_1790[] = {0x2109};
static const unsigned long cp_single_1791[] = {0x064e};
static const unsigned long cp_single_1792[] = {0x064e};
static const unsigned long cp_single_1793[] = {0x064b};
static const unsigned long cp_single_1794[] = {0x3108};
static const unsigned long cp_single_1795[] = {0x24d5};
static const unsigned long cp_single_1796[] = {0x1e1f};
static const unsigned long cp_single_1797[] = {0x0641};
static const unsigned long cp_single_1798[] = {0x0586};
static const unsigned long cp_single_1799[] = {0xfed2};
static const unsigned long cp_single_1800[] = {0xfed3};
static const unsigned long cp_single_1801[] = {0xfed4};
static const unsigned long cp_single_1802[] = {0x03e5};
static const unsigned long cp_single_1803[] = {0x2640};
static const unsigned long cp_single_1804[] = {0xfb00};
static const unsigned long cp_single_1805[] = {0xfb03};
static const unsigned long cp_single_1806[] = {0xfb04};
static const unsigned long cp_single_1807[] = {0xfb01};
static const unsigned long cp_single_1808[] = {0x246e};
static const unsigned long cp_single_1809[] = {0x2482};
static const unsigned long cp_single_1810[] = {0x2496};
static const unsigned long cp_single_1811[] = {0x2012};
static const unsigned long cp_single_1812[] = {0x25a0};
static const unsigned long cp_single_1813[] = {0x25ac};
static const unsigned long cp_single_1814[] = {0x05da};
static const unsigned long cp_single_1815[] = {0xfb3a};
static const unsigned long cp_single_1816[] = {0xfb3a};
static const unsigned long cp_single_1817[] = {0x05da};
static const unsigned long cp_single_1818[] = {0x05dd};
static const unsigned long cp_single_1819[] = {0x05dd};
static const unsigned long cp_single_1820[] = {0x05df};
static const unsigned long cp_single_1821[] = {0x05df};
static const unsigned long cp_single_1822[] = {0x05e3};
static const unsigned long cp_single_1823[] = {0x05e3};
static const unsigned long cp_single_1824[] = {0x05e5};
static const unsigned long cp_single_1825[] = {0x05e5};
static const unsigned long cp_single_1826[] = {0x02c9};
static const unsigned long cp_single_1827[] = {0x25c9};
static const unsigned long cp_single_1828[] = {0x0473};
static const unsigned long cp_single_1829[] = {0x0035};
static const unsigned long cp_single_1830[] = {0x0665};
static const unsigned long cp_single_1831[] = {0x09eb};
static const unsigned long cp_single_1832[] = {0x2464};
static const unsigned long cp_single_1833[] = {0x278e};
static const unsigned long cp_single_1834[] = {0x096b};
static const unsigned long cp_single_1835[] = {0x215d};
static const unsigned long cp_single_1836[] = {0x0aeb};
static const unsigned long cp_single_1837[] = {0x0a6b};
static const unsigned long cp_single_1838[] = {0x0665};
static const unsigned long cp_single_1839[] = {0x3025};
static const unsigned long cp_single_1840[] = {0x3224};
static const unsigned long cp_single_1841[] = {0x2085};
static const unsigned long cp_single_1842[] = {0xff15};
static const unsigned long cp_single_1843[] = {0xf735};
static const unsigned long cp_single_1844[] = {0x2478};
static const unsigned long cp_single_1845[] = {0x248c};
static const unsigned long cp_single_1846[] = {0x06f5};
static const unsigned long cp_single_1847[] = {0x2174};
static const unsigned long cp_single_1848[] = {0x2075};
static const unsigned long cp_single_1849[] = {0x0e55};
static const unsigned long cp_single_1850[] = {0xfb02};
static const unsigned long cp_single_1851[] = {0x0192};
static const unsigned long cp_single_1852[] = {0xff46};
static const unsigned long cp_single_1853[] = {0x3399};
static const unsigned long cp_single_1854[] = {0x0e1f};
static const unsigned long cp_single_1855[] = {0x0e1d};
static const unsigned long cp_single_1856[] = {0x0e4f};
static const unsigned long cp_single_1857[] = {0x2200};
static const unsigned long cp_single_1858[] = {0x0034};
static const unsigned long cp_single_1859[] = {0x0664};
static const unsigned long cp_single_1860[] = {0x09ea};
static const unsigned long cp_single_1861[] = {0x2463};
static const unsigned long cp_single_1862[] = {0x278d};
static const unsigned long cp_single_1863[] = {0x096a};
static const unsigned long cp_single_1864[] = {0x0aea};
static const unsigned long cp_single_1865[] = {0x0a6a};
static const unsigned long cp_single_1866[] = {0x0664};
static const unsigned long cp_single_1867[] = {0x3024};
static const unsigned long cp_single_1868[] = {0x3223};
static const unsigned long cp_single_1869[] = {0x2084};
static const unsigned long cp_single_1870[] = {0xff14};
static const unsigned long cp_single_1871[] = {0x09f7};
static const unsigned long cp_single_1872[] = {0xf734};
static const unsigned long cp_single_1873[] = {0x2477};
static const unsigned long cp_single_1874[] = {0x248b};
static const unsigned long cp_single_1875[] = {0x06f4};
static const unsigned long cp_single_1876[] = {0x2173};
static const unsigned long cp_single_1877[] = {0x2074};
static const unsigned long cp_single_1878[] = {0x246d};
static const unsigned long cp_single_1879[] = {0x2481};
static const unsigned long cp_single_1880[] = {0x2495};
static const unsigned long cp_single_1881[] = {0x0e54};
static const unsigned long cp_single_1882[] = {0x02cb};
static const unsigned long cp_single_1883[] = {0x24a1};
static const unsigned long cp_single_1884[] = {0x2044};
static const unsigned long cp_single_1885[] = {0x20a3};
static const unsigned long cp_single_1886[] = {0x0067};
static const unsigned long cp_single_1887[] = {0x0997};
static const unsigned long cp_single_1888[] = {0x01f5};
static const unsigned long cp_single_1889[] = {0x0917};
static const unsigned long cp_single_1890[] = {0x06af};
static const unsigned long cp_single_1891[] = {0xfb93};
static const unsigned long cp_single_1892[] = {0xfb94};
static const unsigned long cp_single_1893[] = {0xfb95};
static const unsigned long cp_single_1894[] = {0x0a97};
static const unsigned long cp_single_1895[] = {0x0a17};
static const unsigned long cp_single_1896[] = {0x304c};
static const unsigned long cp_single_1897[] = {0x30ac};
static const unsigned long cp_single_1898[] = {0x03b3};
static const unsigned long cp_single_1899[] = {0x0263};
static const unsigned long cp_single_1900[] = {0x02e0};
static const unsigned long cp_single_1901[] = {0x03eb};
static const unsigned long cp_single_1902[] = {0x310d};
static const unsigned long cp_single_1903[] = {0x011f};
static const unsigned long cp_single_1904[] = {0x01e7};
static const unsigned long cp_single_1905[] = {0x0123};
static const unsigned long cp_single_1906[] = {0x24d6};
static const unsigned long cp_single_1907[] = {0x011d};
static const unsigned long cp_single_1908[] = {0x0123};
static const unsigned long cp_single_1909[] = {0x0121};
static const unsigned long cp_single_1910[] = {0x0121};
static const unsigned long cp_single_1911[] = {0x0433};
static const unsigned long cp_single_1912[] = {0x3052};
static const unsigned long cp_single_1913[] = {0x30b2};
static const unsigned long cp_single_1914[] = {0x2251};
static const unsigned long cp_single_1915[] = {0x059c};
static const unsigned long cp_single_1916[] = {0x05f3};
static const unsigned long cp_single_1917[] = {0x059d};
static const unsigned long cp_single_1918[] = {0x00df};
static const unsigned long cp_single_1919[] = {0x059e};
static const unsigned long cp_single_1920[] = {0x05f4};
static const unsigned long cp_single_1921[] = {0x3013};
static const unsigned long cp_single_1922[] = {0x0998};
static const unsigned long cp_single_1923[] = {0x0572};
static const unsigned long cp_single_1924[] = {0x0918};
static const unsigned long cp_single_1925[] = {0x0a98};
static const unsigned long cp_single_1926[] = {0x0a18};
static const unsigned long cp_single_1927[] = {0x063a};
static const unsigned long cp_single_1928[] = {0xfece};
static const unsigned long cp_single_1929[] = {0xfecf};
static const unsigned long cp_single_1930[] = {0xfed0};
static const unsigned long cp_single_1931[] = {0x0495};
static const unsigned long cp_single_1932[] = {0x0493};
static const unsigned long cp_single_1933[] = {0x0491};
static const unsigned long cp_single_1934[] = {0x095a};
static const unsigned long cp_single_1935[] = {0x0a5a};
static const unsigned long cp_single_1936[] = {0x0260};
static const unsigned long cp_single_1937[] = {0x3393};
static const unsigned long cp_single_1938[] = {0x304e};
static const unsigned long cp_single_1939[] = {0x30ae};
static const unsigned long cp_single_1940[] = {0x0563};
static const unsigned long cp_single_1941[] = {0x05d2};
static const unsigned long cp_single_1942[] = {0xfb32};
static const unsigned long cp_single_1943[] = {0xfb32};
static const unsigned long cp_single_1944[] = {0x05d2};
static const unsigned long cp_single_1945[] = {0x0453};
static const unsigned long cp_single_1946[] = {0x01be};
static const unsigned long cp_single_1947[] = {0x0294};
static const unsigned long cp_single_1948[] = {0x0296};
static const unsigned long cp_single_1949[] = {0x02c0};
static const unsigned long cp_single_1950[] = {0x0295};
static const unsigned long cp_single_1951[] = {0x02c1};
static const unsigned long cp_single_1952[] = {0x02e4};
static const unsigned long cp_single_1953[] = {0x02a1};
static const unsigned long cp_single_1954[] = {0x02a2};
static const unsigned long cp_single_1955[] = {0x1e21};
static const unsigned long cp_single_1956[] = {0xff47};
static const unsigned long cp_single_1957[] = {0x3054};
static const unsigned long cp_single_1958[] = {0x30b4};
static const unsigned long cp_single_1959[] = {0x24a2};
static const unsigned long cp_single_1960[] = {0x33ac};
static const unsigned long cp_single_1961[] = {0x2207};
static const unsigned long cp_single_1962[] = {0x0060};
static const unsigned long cp_single_1963[] = {0x0316};
static const unsigned long cp_single_1964[] = {0x0300};
static const unsigned long cp_single_1965[] = {0x0300};
static const unsigned long cp_single_1966[] = {0x0953};
static const unsigned long cp_single_1967[] = {0x02ce};
static const unsigned long cp_single_1968[] = {0xff40};
static const unsigned long cp_single_1969[] = {0x0340};
static const unsigned long cp_single_1970[] = {0x003e};
static const unsigned long cp_single_1971[] = {0x2265};
static const unsigned long cp_single_1972[] = {0x22db};
static const unsigned long cp_single_1973[] = {0xff1e};
static const unsigned long cp_single_1974[] = {0x2273};
static const unsigned long cp_single_1975[] = {0x2277};
static const unsigned long cp_single_1976[] = {0x2267};
static const unsigned long cp_single_1977[] = {0xfe65};
static const unsigned long cp_single_1978[] = {0x0261};
static const unsigned long cp_single_1979[] = {0x01e5};
static const unsigned long cp_single_1980[] = {0x3050};
static const unsigned long cp_single_1981[] = {0x00ab};
static const unsigned long cp_single_1982[] = {0x00bb};
static const unsigned long cp_single_1983[] = {0x2039};
static const unsigned long cp_single_1984[] = {0x203a};
static const unsigned long cp_single_1985[] = {0x30b0};
static const unsigned long cp_single_1986[] = {0x3318};
static const unsigned long cp_single_1987[] = {0x33c9};
static const unsigned long cp_single_1988[] = {0x0068};
static const unsigned long cp_single_1989[] = {0x04a9};
static const unsigned long cp_single_1990[] = {0x06c1};
static const unsigned long cp_single_1991[] = {0x09b9};
static const unsigned long cp_single_1992[] = {0x04b3};
static const unsigned long cp_single_1993[] = {0x0939};
static const unsigned long cp_single_1994[] = {0x0ab9};
static const unsigned long cp_single_1995[] = {0x0a39};
static const unsigned long cp_single_1996[] = {0x062d};
static const unsigned long cp_single_1997[] = {0xfea2};
static const unsigned long cp_single_1998[] = {0xfea3};
static const unsigned long cp_single_1999[] = {0x306f};
static const unsigned long cp_single_2000[] = {0xfea4};
static const unsigned long cp_single_2001[] = {0x332a};
static const unsigned long cp_single_2002[] = {0x30cf};
static const unsigned long cp_single_2003[] = {0xff8a};
static const unsigned long cp_single_2004[] = {0x0a4d};
static const unsigned long cp_single_2005[] = {0x0621};
static const unsigned long cp_single_2006[] = {0x0621};
static const unsigned long cp_single_2007[] = {0x3164};
static const unsigned long cp_single_2008[] = {0x044a};
static const unsigned long cp_single_2009[] = {0x21bc};
static const unsigned long cp_single_2010[] = {0x21c0};
static const unsigned long cp_single_2011[] = {0x33ca};
static const unsigned long cp_single_2012[] = {0x05b2};
static const unsigned long cp_single_2013[] = {0x05b2};
static const unsigned long cp_single_2014[] = {0x05b2};
static const unsigned long cp_single_2015[] = {0x05b2};
static const unsigned long cp_single_2016[] = {0x05b2};
static const unsigned long cp_single_2017[] = {0x05b2};
static const unsigned long cp_single_2018[] = {0x05b2};
static const unsigned long cp_single_2019[] = {0x05b2};
static const unsigned long cp_single_2020[] = {0x05b3};
static const unsigned long cp_single_2021[] = {0x05b3};
static const unsigned long cp_single_2022[] = {0x05b3};
static const unsigned long cp_single_2023[] = {0x05b3};
static const unsigned long cp_single_2024[] = {0x05b3};
static const unsigned long cp_single_2025[] = {0x05b3};
static const unsigned long cp_single_2026[] = {0x05b3};
static const unsigned long cp_single_2027[] = {0x05b3};
static const unsigned long cp_single_2028[] = {0x05b1};
static const unsigned long cp_single_2029[] = {0x05b1};
static const unsigned long cp_single_2030[] = {0x05b1};
static const unsigned long cp_single_2031[] = {0x05b1};
static const unsigned long cp_single_2032[] = {0x05b1};
static const unsigned long cp_single_2033[] = {0x05b1};
static const unsigned long cp_single_2034[] = {0x05b1};
static const unsigned long cp_single_2035[] = {0x05b1};
static const unsigned long cp_single_2036[] = {0x0127};
static const unsigned long cp_single_2037[] = {0x310f};
static const unsigned long cp_single_2038[] = {0x1e2b};
static const unsigned long cp_single_2039[] = {0x1e29};
static const unsigned long cp_single_2040[] = {0x24d7};
static const unsigned long cp_single_2041[] = {0x0125};
static const unsigned long cp_single_2042[] = {0x1e27};
static const unsigned long cp_single_2043[] = {0x1e23};
static const unsigned long cp_single_2044[] = {0x1e25};
static const unsigned long cp_single_2045[] = {0x05d4};
static const unsigned long cp_single_2046[] = {0x2665};
static const unsigned long cp_single_2047[] = {0x2665};
static const unsigned long cp_single_2048[] = {0x2661};
static const unsigned long cp_single_2049[] = {0xfb34};
static const unsigned long cp_single_2050[] = {0xfb34};
static const unsigned long cp_single_2051[] = {0x06c1};
static const unsigned long cp_single_2052[] = {0x0647};
static const unsigned long cp_single_2053[] = {0x05d4};
static const unsigned long cp_single_2054[] = {0xfba7};
static const unsigned long cp_single_2055[] = {0xfeea};
static const unsigned long cp_single_2056[] = {0xfeea};
static const unsigned long cp_single_2057[] = {0xfba5};
static const unsigned long cp_single_2058[] = {0xfba4};
static const unsigned long cp_single_2059[] = {0xfba8};
static const unsigned long cp_single_2060[] = {0xfeeb};
static const unsigned long cp_single_2061[] = {0x3078};
static const unsigned long cp_single_2062[] = {0xfba9};
static const unsigned long cp_single_2063[] = {0xfeec};
static const unsigned long cp_single_2064[] = {0x337b};
static const unsigned long cp_single_2065[] = {0x30d8};
static const unsigned long cp_single_2066[] = {0xff8d};
static const unsigned long cp_single_2067[] = {0x3336};
static const unsigned long cp_single_2068[] = {0x0267};
static const unsigned long cp_single_2069[] = {0x3339};
static const unsigned long cp_single_2070[] = {0x05d7};
static const unsigned long cp_single_2071[] = {0x05d7};
static const unsigned long cp_single_2072[] = {0x0266};
static const unsigned long cp_single_2073[] = {0x02b1};
static const unsigned long cp_single_2074[] = {0x327b};
static const unsigned long cp_single_2075[] = {0x321b};
static const unsigned long cp_single_2076[] = {0x326d};
static const unsigned long cp_single_2077[] = {0x314e};
static const unsigned long cp_single_2078[] = {0x320d};
static const unsigned long cp_single_2079[] = {0x3072};
static const unsigned long cp_single_2080[] = {0x30d2};
static const unsigned long cp_single_2081[] = {0xff8b};
static const unsigned long cp_single_2082[] = {0x05b4};
static const unsigned long cp_single_2083[] = {0x05b4};
static const unsigned long cp_single_2084[] = {0x05b4};
static const unsigned long cp_single_2085[] = {0x05b4};
static const unsigned long cp_single_2086[] = {0x05b4};
static const unsigned long cp_single_2087[] = {0x05b4};
static const unsigned long cp_single_2088[] = {0x05b4};
static const unsigned long cp_single_2089[] = {0x05b4};
static const unsigned long cp_single_2090[] = {0x1e96};
static const unsigned long cp_single_2091[] = {0xff48};
static const unsigned long cp_single_2092[] = {0x0570};
static const unsigned long cp_single_2093[] = {0x0e2b};
static const unsigned long cp_single_2094[] = {0x307b};
static const unsigned long cp_single_2095[] = {0x30db};
static const unsigned long cp_single_2096[] = {0xff8e};
static const unsigned long cp_single_2097[] = {0x05b9};
static const unsigned long cp_single_2098[] = {0x05b9};
static const unsigned long cp_single_2099[] = {0x05b9};
static const unsigned long cp_single_2100[] = {0x05b9};
static const unsigned long cp_single_2101[] = {0x05b9};
static const unsigned long cp_single_2102[] = {0x05b9};
static const unsigned long cp_single_2103[] = {0x05b9};
static const unsigned long cp_single_2104[] = {0x05b9};
static const unsigned long cp_single_2105[] = {0x0e2e};
static const unsigned long cp_single_2106[] = {0x0309};
static const unsigned long cp_single_2107[] = {0x0309};
static const unsigned long cp_single_2108[] = {0x0321};
static const unsigned long cp_single_2109[] = {0x0322};
static const unsigned long cp_single_2110[] = {0x3342};
static const unsigned long cp_single_2111[] = {0x03e9};
static const unsigned long cp_single_2112[] = {0x2015};
static const unsigned long cp_single_2113[] = {0x031b};
static const unsigned long cp_single_2114[] = {0x2668};
static const unsigned long cp_single_2115[] = {0x2302};
static const unsigned long cp_single_2116[] = {0x24a3};
static const unsigned long cp_single_2117[] = {0x02b0};
static const unsigned long cp_single_2118[] = {0x0265};
static const unsigned long cp_single_2119[] = {0x3075};
static const unsigned long cp_single_2120[] = {0x3333};
static const unsigned long cp_single_2121[] = {0x30d5};
static const unsigned long cp_single_2122[] = {0xff8c};
static const unsigned long cp_single_2123[] = {0x02dd};
static const unsigned long cp_single_2124[] = {0x030b};
static const unsigned long cp_single_2125[] = {0x0195};
static const unsigned long cp_single_2126[] = {0x002d};
static const unsigned long cp_single_2127[] = {0xf6e5};
static const unsigned long cp_single_2128[] = {0xff0d};
static const unsigned long cp_single_2129[] = {0xfe63};
static const unsigned long cp_single_2130[] = {0xf6e6};
static const unsigned long cp_single_2131[] = {0x2010};
static const unsigned long cp_single_2132[] = {0x0069};
static const unsigned long cp_single_2133[] = {0x00ed};
static const unsigned long cp_single_2134[] = {0x044f};
static const unsigned long cp_single_2135[] = {0x0987};
static const unsigned long cp_single_2136[] = {0x3127};
static const unsigned long cp_single_2137[] = {0x012d};
static const unsigned long cp_single_2138[] = {0x01d0};
static const unsigned long cp_single_2139[] = {0x24d8};
static const unsigned long cp_single_2140[] = {0x00ee};
static const unsigned long cp_single_2141[] = {0x0456};
static const unsigned long cp_single_2142[] = {0x0209};
static const unsigned long cp_single_2143[] = {0x328f};
static const unsigned long cp_single_2144[] = {0x328b};
static const unsigned long cp_single_2145[] = {0x323f};
static const unsigned long cp_single_2146[] = {0x323a};
static const unsigned long cp_single_2147[] = {0x32a5};
static const unsigned long cp_single_2148[] = {0x3006};
static const unsigned long cp_single_2149[] = {0x3001};
static const unsigned long cp_single_2150[] = {0xff64};
static const unsigned long cp_single_2151[] = {0x3237};
static const unsigned long cp_single_2152[] = {0x32a3};
static const unsigned long cp_single_2153[] = {0x322f};
static const unsigned long cp_single_2154[] = {0x323d};
static const unsigned long cp_single_2155[] = {0x329d};
static const unsigned long cp_single_2156[] = {0x3240};
static const unsigned long cp_single_2157[] = {0x3296};
static const unsigned long cp_single_2158[] = {0x3236};
static const unsigned long cp_single_2159[] = {0x322b};
static const unsigned long cp_single_2160[] = {0x3232};
static const unsigned long cp_single_2161[] = {0x32a4};
static const unsigned long cp_single_2162[] = {0x3005};
static const unsigned long cp_single_2163[] = {0x3298};
static const unsigned long cp_single_2164[] = {0x3238};
static const unsigned long cp_single_2165[] = {0x32a7};
static const unsigned long cp_single_2166[] = {0x32a6};
static const unsigned long cp_single_2167[] = {0x32a9};
static const unsigned long cp_single_2168[] = {0x322e};
static const unsigned long cp_single_2169[] = {0x322a};
static const unsigned long cp_single_2170[] = {0x3234};
static const unsigned long cp_single_2171[] = {0x3002};
static const unsigned long cp_single_2172[] = {0x329e};
static const unsigned long cp_single_2173[] = {0x3243};
static const unsigned long cp_single_2174[] = {0x3239};
static const unsigned long cp_single_2175[] = {0x323e};
static const unsigned long cp_single_2176[] = {0x32a8};
static const unsigned long cp_single_2177[] = {0x3299};
static const unsigned long cp_single_2178[] = {0x3242};
static const unsigned long cp_single_2179[] = {0x3233};
static const unsigned long cp_single_2180[] = {0x3000};
static const unsigned long cp_single_2181[] = {0x3235};
static const unsigned long cp_single_2182[] = {0x3231};
static const unsigned long cp_single_2183[] = {0x323b};
static const unsigned long cp_single_2184[] = {0x3230};
static const unsigned long cp_single_2185[] = {0x323c};
static const unsigned long cp_single_2186[] = {0x322c};
static const unsigned long cp_single_2187[] = {0x322d};
static const unsigned long cp_single_2188[] = {0x3007};
static const unsigned long cp_single_2189[] = {0x328e};
static const unsigned long cp_single_2190[] = {0x328a};
static const unsigned long cp_single_2191[] = {0x3294};
static const unsigned long cp_single_2192[] = {0x3290};
static const unsigned long cp_single_2193[] = {0x328c};
static const unsigned long cp_single_2194[] = {0x328d};
static const unsigned long cp_single_2195[] = {0x0907};
static const unsigned long cp_single_2196[] = {0x00ef};
static const unsigned long cp_single_2197[] = {0x1e2f};
static const unsigned long cp_single_2198[] = {0x04e5};
static const unsigned long cp_single_2199[] = {0x1ecb};
static const unsigned long cp_single_2200[] = {0x04d7};
static const unsigned long cp_single_2201[] = {0x0435};
static const unsigned long cp_single_2202[] = {0x3275};
static const unsigned long cp_single_2203[] = {0x3215};
static const unsigned long cp_single_2204[] = {0x3267};
static const unsigned long cp_single_2205[] = {0x3147};
static const unsigned long cp_single_2206[] = {0x3207};
static const unsigned long cp_single_2207[] = {0x00ec};
static const unsigned long cp_single_2208[] = {0x0a87};
static const unsigned long cp_single_2209[] = {0x0a07};
static const unsigned long cp_single_2210[] = {0x3044};
static const unsigned long cp_single_2211[] = {0x1ec9};
static const unsigned long cp_single_2212[] = {0x0988};
static const unsigned long cp_single_2213[] = {0x0438};
static const unsigned long cp_single_2214[] = {0x0908};
static const unsigned long cp_single_2215[] = {0x0a88};
static const unsigned long cp_single_2216[] = {0x0a08};
static const unsigned long cp_single_2217[] = {0x0a40};
static const unsigned long cp_single_2218[] = {0x020b};
static const unsigned long cp_single_2219[] = {0x0439};
static const unsigned long cp_single_2220[] = {0x09c0};
static const unsigned long cp_single_2221[] = {0x0940};
static const unsigned long cp_single_2222[] = {0x0ac0};
static const unsigned long cp_single_2223[] = {0x0133};
static const unsigned long cp_single_2224[] = {0x30a4};
static const unsigned long cp_single_2225[] = {0xff72};
static const unsigned long cp_single_2226[] = {0x3163};
static const unsigned long cp_single_2227[] = {0x02dc};
static const unsigned long cp_single_2228[] = {0x05ac};
static const unsigned long cp_single_2229[] = {0x012b};
static const unsigned long cp_single_2230[] = {0x04e3};
static const unsigned long cp_single_2231[] = {0x2253};
static const unsigned long cp_single_2232[] = {0x0a3f};
static const unsigned long cp_single_2233[] = {0xff49};
static const unsigned long cp_single_2234[] = {0x2206};
static const unsigned long cp_single_2235[] = {0x221e};
static const unsigned long cp_single_2236[] = {0x056b};
static const unsigned long cp_single_2237[] = {0x222b};
static const unsigned long cp_single_2238[] = {0x2321};
static const unsigned long cp_single_2239[] = {0x2321};
static const unsigned long cp_single_2240[] = {0xf8f5};
static const unsigned long cp_single_2241[] = {0x2320};
static const unsigned long cp_single_2242[] = {0x2320};
static const unsigned long cp_single_2243[] = {0x2229};
static const unsigned long cp_single_2244[] = {0x3305};
static const unsigned long cp_single_2245[] = {0x25d8};
static const unsigned long cp_single_2246[] = {0x25d9};
static const unsigned long cp_single_2247[] = {0x263b};
static const unsigned long cp_single_2248[] = {0x0451};
static const unsigned long cp_single_2249[] = {0x012f};
static const unsigned long cp_single_2250[] = {0x03b9};
static const unsigned long cp_single_2251[] = {0x03ca};
static const unsigned long cp_single_2252[] = {0x0390};
static const unsigned long cp_single_2253[] = {0x0269};
static const unsigned long cp_single_2254[] = {0x03af};
static const unsigned long cp_single_2255[] = {0x24a4};
static const unsigned long cp_single_2256[] = {0x0a72};
static const unsigned long cp_single_2257[] = {0x3043};
static const unsigned long cp_single_2258[] = {0x30a3};
static const unsigned long cp_single_2259[] = {0xff68};
static const unsigned long cp_single_2260[] = {0x09fa};
static const unsigned long cp_single_2261[] = {0x0268};
static const unsigned long cp_single_2262[] = {0xf6ed};
static const unsigned long cp_single_2263[] = {0x309d};
static const unsigned long cp_single_2264[] = {0x30fd};
static const unsigned long cp_single_2265[] = {0x0129};
static const unsigned long cp_single_2266[] = {0x1e2d};
static const unsigned long cp_single_2267[] = {0x3129};
static const unsigned long cp_single_2268[] = {0x044e};
static const unsigned long cp_single_2269[] = {0x09bf};
static const unsigned long cp_single_2270[] = {0x093f};
static const unsigned long cp_single_2271[] = {0x0abf};
static const unsigned long cp_single_2272[] = {0x0475};
static const unsigned long cp_single_2273[] = {0x0477};
static const unsigned long cp_single_2274[] = {0x006a};
static const unsigned long cp_single_2275[] = {0x0571};
static const unsigned long cp_single_2276[] = {0x099c};
static const unsigned long cp_single_2277[] = {0x091c};
static const unsigned long cp_single_2278[] = {0x0a9c};
static const unsigned long cp_single_2279[] = {0x0a1c};
static const unsigned long cp_single_2280[] = {0x3110};
static const unsigned long cp_single_2281[] = {0x01f0};
static const unsigned long cp_single_2282[] = {0x24d9};
static const unsigned long cp_single_2283[] = {0x0135};
static const unsigned long cp_single_2284[] = {0x029d};
static const unsigned long cp_single_2285[] = {0x025f};
static const unsigned long cp_single_2286[] = {0x0458};
static const unsigned long cp_single_2287[] = {0x062c};
static const unsigned long cp_single_2288[] = {0xfe9e};
static const unsigned long cp_single_2289[] = {0xfe9f};
static const unsigned long cp_single_2290[] = {0xfea0};
static const unsigned long cp_single_2291[] = {0x0698};
static const unsigned long cp_single_2292[] = {0xfb8b};
static const unsigned long cp_single_2293[] = {0x099d};
static const unsigned long cp_single_2294[] = {0x091d};
static const unsigned long cp_single_2295[] = {0x0a9d};
static const unsigned long cp_single_2296[] = {0x0a1d};
static const unsigned long cp_single_2297[] = {0x057b};
static const unsigned long cp_single_2298[] = {0x3004};
static const unsigned long cp_single_2299[] = {0xff4a};
static const unsigned long cp_single_2300[] = {0x24a5};
static const unsigned long cp_single_2301[] = {0x02b2};
static const unsigned long cp_single_2302[] = {0x006b};
static const unsigned long cp_single_2303[] = {0x04a1};
static const unsigned long cp_single_2304[] = {0x0995};
static const unsigned long cp_single_2305[] = {0x1e31};
static const unsigned long cp_single_2306[] = {0x043a};
static const unsigned long cp_single_2307[] = {0x049b};
static const unsigned long cp_single_2308[] = {0x0915};
static const unsigned long cp_single_2309[] = {0x05db};
static const unsigned long cp_single_2310[] = {0x0643};
static const unsigned long cp_single_2311[] = {0xfb3b};
static const unsigned long cp_single_2312[] = {0xfb3b};
static const unsigned long cp_single_2313[] = {0xfeda};
static const unsigned long cp_single_2314[] = {0x05db};
static const unsigned long cp_single_2315[] = {0xfedb};
static const unsigned long cp_single_2316[] = {0xfedc};
static const unsigned long cp_single_2317[] = {0xfb4d};
static const unsigned long cp_single_2318[] = {0x0a95};
static const unsigned long cp_single_2319[] = {0x0a15};
static const unsigned long cp_single_2320[] = {0x304b};
static const unsigned long cp_single_2321[] = {0x04c4};
static const unsigned long cp_single_2322[] = {0x30ab};
static const unsigned long cp_single_2323[] = {0xff76};
static const unsigned long cp_single_2324[] = {0x03ba};
static const unsigned long cp_single_2325[] = {0x03f0};
static const unsigned long cp_single_2326[] = {0x3171};
static const unsigned long cp_single_2327[] = {0x3184};
static const unsigned long cp_single_2328[] = {0x3178};
static const unsigned long cp_single_2329[] = {0x3179};
static const unsigned long cp_single_2330[] = {0x330d};
static const unsigned long cp_single_2331[] = {0x0640};
static const unsigned long cp_single_2332[] = {0x0640};
static const unsigned long cp_single_2333[] = {0x30f5};
static const unsigned long cp_single_2334[] = {0x3384};
static const unsigned long cp_single_2335[] = {0x0650};
static const unsigned long cp_single_2336[] = {0x064d};
static const unsigned long cp_single_2337[] = {0x049f};
static const unsigned long cp_single_2338[] = {0xff70};
static const unsigned long cp_single_2339[] = {0x049d};
static const unsigned long cp_single_2340[] = {0x310e};
static const unsigned long cp_single_2341[] = {0x3389};
static const unsigned long cp_single_2342[] = {0x01e9};
static const unsigned long cp_single_2343[] = {0x0137};
static const unsigned long cp_single_2344[] = {0x24da};
static const unsigned long cp_single_2345[] = {0x0137};
static const unsigned long cp_single_2346[] = {0x1e33};
static const unsigned long cp_single_2347[] = {0x0584};
static const unsigned long cp_single_2348[] = {0x3051};
static const unsigned long cp_single_2349[] = {0x30b1};
static const unsigned long cp_single_2350[] = {0xff79};
static const unsigned long cp_single_2351[] = {0x056f};
static const unsigned long cp_single_2352[] = {0x30f6};
static const unsigned long cp_single_2353[] = {0x0138};
static const unsigned long cp_single_2354[] = {0x0996};
static const unsigned long cp_single_2355[] = {0x0445};
static const unsigned long cp_single_2356[] = {0x0916};
static const unsigned long cp_single_2357[] = {0x0a96};
static const unsigned long cp_single_2358[] = {0x0a16};
static const unsigned long cp_single_2359[] = {0x062e};
static const unsigned long cp_single_2360[] = {0xfea6};
static const unsigned long cp_single_2361[] = {0xfea7};
static const unsigned long cp_single_2362[] = {0xfea8};
static const unsigned long cp_single_2363[] = {0x03e7};
static const unsigned long cp_single_2364[] = {0x0959};
static const unsigned long cp_single_2365[] = {0x0a59};
static const unsigned long cp_single_2366[] = {0x3278};
static const unsigned long cp_single_2367[] = {0x3218};
static const unsigned long cp_single_2368[] = {0x326a};
static const unsigned long cp_single_2369[] = {0x314b};
static const unsigned long cp_single_2370[] = {0x320a};
static const unsigned long cp_single_2371[] = {0x0e02};
static const unsigned long cp_single_2372[] = {0x0e05};
static const unsigned long cp_single_2373[] = {0x0e03};
static const unsigned long cp_single_2374[] = {0x0e04};
static const unsigned long cp_single_2375[] = {0x0e5b};
static const unsigned long cp_single_2376[] = {0x0199};
static const unsigned long cp_single_2377[] = {0x0e06};
static const unsigned long cp_single_2378[] = {0x3391};
static const unsigned long cp_single_2379[] = {0x304d};
static const unsigned long cp_single_2380[] = {0x30ad};
static const unsigned long cp_single_2381[] = {0xff77};
static const unsigned long cp_single_2382[] = {0x3315};
static const unsigned long cp_single_2383[] = {0x3316};
static const unsigned long cp_single_2384[] = {0x3314};
static const unsigned long cp_single_2385[] = {0x326e};
static const unsigned long cp_single_2386[] = {0x320e};
static const unsigned long cp_single_2387[] = {0x3260};
static const unsigned long cp_single_2388[] = {0x3131};
static const unsigned long cp_single_2389[] = {0x3200};
static const unsigned long cp_single_2390[] = {0x3133};
static const unsigned long cp_single_2391[] = {0x045c};
static const unsigned long cp_single_2392[] = {0x1e35};
static const unsigned long cp_single_2393[] = {0x3398};
static const unsigned long cp_single_2394[] = {0x33a6};
static const unsigned long cp_single_2395[] = {0xff4b};
static const unsigned long cp_single_2396[] = {0x33a2};
static const unsigned long cp_single_2397[] = {0x3053};
static const unsigned long cp_single_2398[] = {0x33c0};
static const unsigned long cp_single_2399[] = {0x0e01};
static const unsigned long cp_single_2400[] = {0x30b3};
static const unsigned long cp_single_2401[] = {0xff7a};
static const unsigned long cp_single_2402[] = {0x331e};
static const unsigned long cp_single_2403[] = {0x0481};
static const unsigned long cp_single_2404[] = {0x327f};
static const unsigned long cp_single_2405[] = {0x0343};
static const unsigned long cp_single_2406[] = {0x24a6};
static const unsigned long cp_single_2407[] = {0x33aa};
static const unsigned long cp_single_2408[] = {0x046f};
static const unsigned long cp_single_2409[] = {0x33cf};
static const unsigned long cp_single_2410[] = {0x029e};
static const unsigned long cp_single_2411[] = {0x304f};
static const unsigned long cp_single_2412[] = {0x30af};
static const unsigned long cp_single_2413[] = {0xff78};
static const unsigned long cp_single_2414[] = {0x33b8};
static const unsigned long cp_single_2415[] = {0x33be};
static const unsigned long cp_single_2416[] = {0x006c};
static const unsigned long cp_single_2417[] = {0x09b2};
static const unsigned long cp_single_2418[] = {0x013a};
static const unsigned long cp_single_2419[] = {0x0932};
static const unsigned long cp_single_2420[] = {0x0ab2};
static const unsigned long cp_single_2421[] = {0x0a32};
static const unsigned long cp_single_2422[] = {0x0e45};
static const unsigned long cp_single_2423[] = {0xfefc};
static const unsigned long cp_single_2424[] = {0xfef8};
static const unsigned long cp_single_2425[] = {0xfef7};
static const unsigned long cp_single_2426[] = {0xfefa};
static const unsigned long cp_single_2427[] = {0xfef9};
static const unsigned long cp_single_2428[] = {0xfefb};
static const unsigned long cp_single_2429[] = {0xfef6};
static const unsigned long cp_single_2430[] = {0xfef5};
static const unsigned long cp_single_2431[] = {0x0644};
static const unsigned long cp_single_2432[] = {0x03bb};
static const unsigned long cp_single_2433[] = {0x019b};
static const unsigned long cp_single_2434[] = {0x05dc};
static const unsigned long cp_single_2435[] = {0xfb3c};
static const unsigned long cp_single_2436[] = {0xfb3c};
static const unsigned long cp_single_2437[] = {0x05dc};
static const unsigned long cp_single_2438[] = {0xfede};
static const unsigned long cp_single_2439[] = {0xfcca};
static const unsigned long cp_single_2440[] = {0xfedf};
static const unsigned long cp_single_2441[] = {0xfcc9};
static const unsigned long cp_single_2442[] = {0xfccb};
static const unsigned long cp_single_2443[] = {0xfdf2};
static const unsigned long cp_single_2444[] = {0xfee0};
static const unsigned long cp_single_2445[] = {0xfd88};
static const unsigned long cp_single_2446[] = {0xfccc};
static const unsigned long cp_single_2447[] = {0x25ef};
static const unsigned long cp_single_2448[] = {0x019a};
static const unsigned long cp_single_2449[] = {0x026c};
static const unsigned long cp_single_2450[] = {0x310c};
static const unsigned long cp_single_2451[] = {0x013e};
static const unsigned long cp_single_2452[] = {0x013c};
static const unsigned long cp_single_2453[] = {0x24db};
static const unsigned long cp_single_2454[] = {0x1e3d};
static const unsigned long cp_single_2455[] = {0x013c};
static const unsigned long cp_single_2456[] = {0x0140};
static const unsigned long cp_single_2457[] = {0x0140};
static const unsigned long cp_single_2458[] = {0x1e37};
static const unsigned long cp_single_2459[] = {0x1e39};
static const unsigned long cp_single_2460[] = {0x031a};
static const unsigned long cp_single_2461[] = {0x0318};
static const unsigned long cp_single_2462[] = {0x003c};
static const unsigned long cp_single_2463[] = {0x2264};
static const unsigned long cp_single_2464[] = {0x22da};
static const unsigned long cp_single_2465[] = {0xff1c};
static const unsigned long cp_single_2466[] = {0x2272};
static const unsigned long cp_single_2467[] = {0x2276};
static const unsigned long cp_single_2468[] = {0x2266};
static const unsigned long cp_single_2469[] = {0xfe64};
static const unsigned long cp_single_2470[] = {0x026e};
static const unsigned long cp_single_2471[] = {0x258c};
static const unsigned long cp_single_2472[] = {0x026d};
static const unsigned long cp_single_2473[] = {0x20a4};
static const unsigned long cp_single_2474[] = {0x056c};
static const unsigned long cp_single_2475[] = {0x01c9};
static const unsigned long cp_single_2476[] = {0x0459};
static const unsigned long cp_single_2477[] = {0xf6c0};
static const unsigned long cp_single_2478[] = {0x0933};
static const unsigned long cp_single_2479[] = {0x0ab3};
static const unsigned long cp_single_2480[] = {0x1e3b};
static const unsigned long cp_single_2481[] = {0x0934};
static const unsigned long cp_single_2482[] = {0x09e1};
static const unsigned long cp_single_2483[] = {0x0961};
static const unsigned long cp_single_2484[] = {0x09e3};
static const unsigned long cp_single_2485[] = {0x0963};
static const unsigned long cp_single_2486[] = {0x026b};
static const unsigned long cp_single_2487[] = {0xff4c};
static const unsigned long cp_single_2488[] = {0x33d0};
static const unsigned long cp_single_2489[] = {0x0e2c};
static const unsigned long cp_single_2490[] = {0x2227};
static const unsigned long cp_single_2491[] = {0x00ac};
static const unsigned long cp_single_2492[] = {0x2310};
static const unsigned long cp_single_2493[] = {0x2228};
static const unsigned long cp_single_2494[] = {0x0e25};
static const unsigned long cp_single_2495[] = {0x017f};
static const unsigned long cp_single_2496[] = {0xfe4e};
static const unsigned long cp_single_2497[] = {0x0332};
static const unsigned long cp_single_2498[] = {0xfe4d};
static const unsigned long cp_single_2499[] = {0x25ca};
static const unsigned long cp_single_2500[] = {0x24a7};
static const unsigned long cp_single_2501[] = {0x0142};
static const unsigned long cp_single_2502[] = {0x2113};
static const unsigned long cp_single_2503[] = {0xf6ee};
static const unsigned long cp_single_2504[] = {0x2591};
static const unsigned long cp_single_2505[] = {0x0e26};
static const unsigned long cp_single_2506[] = {0x098c};
static const unsigned long cp_single_2507[] = {0x090c};
static const unsigned long cp_single_2508[] = {0x09e2};
static const unsigned long cp_single_2509[] = {0x0962};
static const unsigned long cp_single_2510[] = {0x33d3};
static const unsigned long cp_single_2511[] = {0x006d};
static const unsigned long cp_single_2512[] = {0x09ae};
static const unsigned long cp_single_2513[] = {0x00af};
static const unsigned long cp_single_2514[] = {0x0331};
static const unsigned long cp_single_2515[] = {0x0304};
static const unsigned long cp_single_2516[] = {0x02cd};
static const unsigned long cp_single_2517[] = {0xffe3};
static const unsigned long cp_single_2518[] = {0x1e3f};
static const unsigned long cp_single_2519[] = {0x092e};
static const unsigned long cp_single_2520[] = {0x0aae};
static const unsigned long cp_single_2521[] = {0x0a2e};
static const unsigned long cp_single_2522[] = {0x05a4};
static const unsigned long cp_single_2523[] = {0x05a4};
static const unsigned long cp_single_2524[] = {0x307e};
static const unsigned long cp_single_2525[] = {0xf895};
static const unsigned long cp_single_2526[] = {0xf894};
static const unsigned long cp_single_2527[] = {0x0e4b};
static const unsigned long cp_single_2528[] = {0xf893};
static const unsigned long cp_single_2529[] = {0xf88c};
static const unsigned long cp_single_2530[] = {0xf88b};
static const unsigned long cp_single_2531[] = {0x0e48};
static const unsigned long cp_single_2532[] = {0xf88a};
static const unsigned long cp_single_2533[] = {0xf884};
static const unsigned long cp_single_2534[] = {0x0e31};
static const unsigned long cp_single_2535[] = {0xf889};
static const unsigned long cp_single_2536[] = {0x0e47};
static const unsigned long cp_single_2537[] = {0xf88f};
static const unsigned long cp_single_2538[] = {0xf88e};
static const unsigned long cp_single_2539[] = {0x0e49};
static const unsigned long cp_single_2540[] = {0xf88d};
static const unsigned long cp_single_2541[] = {0xf892};
static const unsigned long cp_single_2542[] = {0xf891};
static const unsigned long cp_single_2543[] = {0x0e4a};
static const unsigned long cp_single_2544[] = {0xf890};
static const unsigned long cp_single_2545[] = {0x0e46};
static const unsigned long cp_single_2546[] = {0x30de};
static const unsigned long cp_single_2547[] = {0xff8f};
static const unsigned long cp_single_2548[] = {0x2642};
static const unsigned long cp_single_2549[] = {0x3347};
static const unsigned long cp_single_2550[] = {0x05be};
static const unsigned long cp_single_2551[] = {0x2642};
static const unsigned long cp_single_2552[] = {0x05af};
static const unsigned long cp_single_2553[] = {0x3383};
static const unsigned long cp_single_2554[] = {0x3107};
static const unsigned long cp_single_2555[] = {0x33d4};
static const unsigned long cp_single_2556[] = {0x24dc};
static const unsigned long cp_single_2557[] = {0x33a5};
static const unsigned long cp_single_2558[] = {0x1e41};
static const unsigned long cp_single_2559[] = {0x1e43};
static const unsigned long cp_single_2560[] = {0x0645};
static const unsigned long cp_single_2561[] = {0xfee2};
static const unsigned long cp_single_2562[] = {0xfee3};
static const unsigned long cp_single_2563[] = {0xfee4};
static const unsigned long cp_single_2564[] = {0xfcd1};
static const unsigned long cp_single_2565[] = {0xfc48};
static const unsigned long cp_single_2566[] = {0x334d};
static const unsigned long cp_single_2567[] = {0x3081};
static const unsigned long cp_single_2568[] = {0x337e};
static const unsigned long cp_single_2569[] = {0x30e1};
static const unsigned long cp_single_2570[] = {0xff92};
static const unsigned long cp_single_2571[] = {0x05de};
static const unsigned long cp_single_2572[] = {0xfb3e};
static const unsigned long cp_single_2573[] = {0xfb3e};
static const unsigned long cp_single_2574[] = {0x05de};
static const unsigned long cp_single_2575[] = {0x0574};
static const unsigned long cp_single_2576[] = {0x05a5};
static const unsigned long cp_single_2577[] = {0x05a6};
static const unsigned long cp_single_2578[] = {0x05a6};
static const unsigned long cp_single_2579[] = {0x05a5};
static const unsigned long cp_single_2580[] = {0x0271};
static const unsigned long cp_single_2581[] = {0x3392};
static const unsigned long cp_single_2582[] = {0xff65};
static const unsigned long cp_single_2583[] = {0x00b7};
static const unsigned long cp_single_2584[] = {0x3272};
static const unsigned long cp_single_2585[] = {0x3212};
static const unsigned long cp_single_2586[] = {0x3264};
static const unsigned long cp_single_2587[] = {0x3141};
static const unsigned long cp_single_2588[] = {0x3170};
static const unsigned long cp_single_2589[] = {0x3204};
static const unsigned long cp_single_2590[] = {0x316e};
static const unsigned long cp_single_2591[] = {0x316f};
static const unsigned long cp_single_2592[] = {0x307f};
static const unsigned long cp_single_2593[] = {0x30df};
static const unsigned long cp_single_2594[] = {0xff90};
static const unsigned long cp_single_2595[] = {0x2212};
static const unsigned long cp_single_2596[] = {0x0320};
static const unsigned long cp_single_2597[] = {0x2296};
static const unsigned long cp_single_2598[] = {0x02d7};
static const unsigned long cp_single_2599[] = {0x2213};
static const unsigned long cp_single_2600[] = {0x2032};
static const unsigned long cp_single_2601[] = {0x334a};
static const unsigned long cp_single_2602[] = {0x3349};
static const unsigned long cp_single_2603[] = {0x0270};
static const unsigned long cp_single_2604[] = {0x3396};
static const unsigned long cp_single_2605[] = {0x33a3};
static const unsigned long cp_single_2606[] = {0xff4d};
static const unsigned long cp_single_2607[] = {0x339f};
static const unsigned long cp_single_2608[] = {0x3082};
static const unsigned long cp_single_2609[] = {0x33c1};
static const unsigned long cp_single_2610[] = {0x30e2};
static const unsigned long cp_single_2611[] = {0xff93};
static const unsigned long cp_single_2612[] = {0x33d6};
static const unsigned long cp_single_2613[] = {0x0e21};
static const unsigned long cp_single_2614[] = {0x33a7};
static const unsigned long cp_single_2615[] = {0x33a8};
static const unsigned long cp_single_2616[] = {0x24a8};
static const unsigned long cp_single_2617[] = {0x33ab};
static const unsigned long cp_single_2618[] = {0x33b3};
static const unsigned long cp_single_2619[] = {0xf6ef};
static const unsigned long cp_single_2620[] = {0x026f};
static const unsigned long cp_single_2621[] = {0x00b5};
static const unsigned long cp_single_2622[] = {0x00b5};
static const unsigned long cp_single_2623[] = {0x3382};
static const unsigned long cp_single_2624[] = {0x226b};
static const unsigned long cp_single_2625[] = {0x226a};
static const unsigned long cp_single_2626[] = {0x338c};
static const unsigned long cp_single_2627[] = {0x03bc};
static const unsigned long cp_single_2628[] = {0x338d};
static const unsigned long cp_single_2629[] = {0x3080};
static const unsigned long cp_single_2630[] = {0x30e0};
static const unsigned long cp_single_2631[] = {0xff91};
static const unsigned long cp_single_2632[] = {0x3395};
static const unsigned long cp_single_2633[] = {0x00d7};
static const unsigned long cp_single_2634[] = {0x339b};
static const unsigned long cp_single_2635[] = {0x05a3};
static const unsigned long cp_single_2636[] = {0x05a3};
static const unsigned long cp_single_2637[] = {0x266a};
static const unsigned long cp_single_2638[] = {0x266b};
static const unsigned long cp_single_2639[] = {0x266d};
static const unsigned long cp_single_2640[] = {0x266f};
static const unsigned long cp_single_2641[] = {0x33b2};
static const unsigned long cp_single_2642[] = {0x33b6};
static const unsigned long cp_single_2643[] = {0x33bc};
static const unsigned long cp_single_2644[] = {0x33b9};
static const unsigned long cp_single_2645[] = {0x33b7};
static const unsigned long cp_single_2646[] = {0x33bf};
static const unsigned long cp_single_2647[] = {0x33bd};
static const unsigned long cp_single_2648[] = {0x006e};
static const unsigned long cp_single_2649[] = {0x09a8};
static const unsigned long cp_single_2650[] = {0x2207};
static const unsigned long cp_single_2651[] = {0x0144};
static const unsigned long cp_single_2652[] = {0x0928};
static const unsigned long cp_single_2653[] = {0x0aa8};
static const unsigned long cp_single_2654[] = {0x0a28};
static const unsigned long cp_single_2655[] = {0x306a};
static const unsigned long cp_single_2656[] = {0x30ca};
static const unsigned long cp_single_2657[] = {0xff85};
static const unsigned long cp_single_2658[] = {0x0149};
static const unsigned long cp_single_2659[] = {0x3381};
static const unsigned long cp_single_2660[] = {0x310b};
static const unsigned long cp_single_2661[] = {0x00a0};
static const unsigned long cp_single_2662[] = {0x0148};
static const unsigned long cp_single_2663[] = {0x0146};
static const unsigned long cp_single_2664[] = {0x24dd};
static const unsigned long cp_single_2665[] = {0x1e4b};
static const unsigned long cp_single_2666[] = {0x0146};
static const unsigned long cp_single_2667[] = {0x1e45};
static const unsigned long cp_single_2668[] = {0x1e47};
static const unsigned long cp_single_2669[] = {0x306d};
static const unsigned long cp_single_2670[] = {0x30cd};
static const unsigned long cp_single_2671[] = {0xff88};
static const unsigned long cp_single_2672[] = {0x20aa};
static const unsigned long cp_single_2673[] = {0x338b};
static const unsigned long cp_single_2674[] = {0x0999};
static const unsigned long cp_single_2675[] = {0x0919};
static const unsigned long cp_single_2676[] = {0x0a99};
static const unsigned long cp_single_2677[] = {0x0a19};
static const unsigned long cp_single_2678[] = {0x0e07};
static const unsigned long cp_single_2679[] = {0x3093};
static const unsigned long cp_single_2680[] = {0x0272};
static const unsigned long cp_single_2681[] = {0x0273};
static const unsigned long cp_single_2682[] = {0x326f};
static const unsigned long cp_single_2683[] = {0x320f};
static const unsigned long cp_single_2684[] = {0x3135};
static const unsigned long cp_single_2685[] = {0x3261};
static const unsigned long cp_single_2686[] = {0x3136};
static const unsigned long cp_single_2687[] = {0x3134};
static const unsigned long cp_single_2688[] = {0x3168};
static const unsigned long cp_single_2689[] = {0x3201};
static const unsigned long cp_single_2690[] = {0x3167};
static const unsigned long cp_single_2691[] = {0x3166};
static const unsigned long cp_single_2692[] = {0x306b};
static const unsigned long cp_single_2693[] = {0x30cb};
static const unsigned long cp_single_2694[] = {0xff86};
static const unsigned long cp_single_2695[] = {0xf899};
static const unsigned long cp_single_2696[] = {0x0e4d};
static const unsigned long cp_single_2697[] = {0x0039};
static const unsigned long cp_single_2698[] = {0x0669};
static const unsigned long cp_single_2699[] = {0x09ef};
static const unsigned long cp_single_2700[] = {0x2468};
static const unsigned long cp_single_2701[] = {0x2792};
static const unsigned long cp_single_2702[] = {0x096f};
static const unsigned long cp_single_2703[] = {0x0aef};
static const unsigned long cp_single_2704[] = {0x0a6f};
static const unsigned long cp_single_2705[] = {0x0669};
static const unsigned long cp_single_2706[] = {0x3029};
static const unsigned long cp_single_2707[] = {0x3228};
static const unsigned long cp_single_2708[] = {0x2089};
static const unsigned long cp_single_2709[] = {0xff19};
static const unsigned long cp_single_2710[] = {0xf739};
static const unsigned long cp_single_2711[] = {0x247c};
static const unsigned long cp_single_2712[] = {0x2490};
static const unsigned long cp_single_2713[] = {0x06f9};
static const unsigned long cp_single_2714[] = {0x2178};
static const unsigned long cp_single_2715[] = {0x2079};
static const unsigned long cp_single_2716[] = {0x2472};
static const unsigned long cp_single_2717[] = {0x2486};
static const unsigned long cp_single_2718[] = {0x249a};
static const unsigned long cp_single_2719[] = {0x0e59};
static const unsigned long cp_single_2720[] = {0x01cc};
static const unsigned long cp_single_2721[] = {0x045a};
static const unsigned long cp_single_2722[] = {0x30f3};
static const unsigned long cp_single_2723[] = {0xff9d};
static const unsigned long cp_single_2724[] = {0x019e};
static const unsigned long cp_single_2725[] = {0x1e49};
static const unsigned long cp_single_2726[] = {0xff4e};
static const unsigned long cp_single_2727[] = {0x339a};
static const unsigned long cp_single_2728[] = {0x09a3};
static const unsigned long cp_single_2729[] = {0x0923};
static const unsigned long cp_single_2730[] = {0x0aa3};
static const unsigned long cp_single_2731[] = {0x0a23};
static const unsigned long cp_single_2732[] = {0x0929};
static const unsigned long cp_single_2733[] = {0x306e};
static const unsigned long cp_single_2734[] = {0x30ce};
static const unsigned long cp_single_2735[] = {0xff89};
static const unsigned long cp_single_2736[] = {0x00a0};
static const unsigned long cp_single_2737[] = {0x0e13};
static const unsigned long cp_single_2738[] = {0x0e19};
static const unsigned long cp_single_2739[] = {0x0646};
static const unsigned long cp_single_2740[] = {0xfee6};
static const unsigned long cp_single_2741[] = {0x06ba};
static const unsigned long cp_single_2742[] = {0xfb9f};
static const unsigned long cp_single_2743[] = {0xfee7};
static const unsigned long cp_single_2744[] = {0xfcd2};
static const unsigned long cp_single_2745[] = {0xfc4b};
static const unsigned long cp_single_2746[] = {0xfee8};
static const unsigned long cp_single_2747[] = {0xfcd5};
static const unsigned long cp_single_2748[] = {0xfc4e};
static const unsigned long cp_single_2749[] = {0xfc8d};
static const unsigned long cp_single_2750[] = {0x220c};
static const unsigned long cp_single_2751[] = {0x2209};
static const unsigned long cp_single_2752[] = {0x2209};
static const unsigned long cp_single_2753[] = {0x2260};
static const unsigned long cp_single_2754[] = {0x226f};
static const unsigned long cp_single_2755[] = {0x2271};
static const unsigned long cp_single_2756[] = {0x2279};
static const unsigned long cp_single_2757[] = {0x2262};
static const unsigned long cp_single_2758[] = {0x226e};
static const unsigned long cp_single_2759[] = {0x2270};
static const unsigned long cp_single_2760[] = {0x2226};
static const unsigned long cp_single_2761[] = {0x2280};
static const unsigned long cp_single_2762[] = {0x2284};
static const unsigned long cp_single_2763[] = {0x2281};
static const unsigned long cp_single_2764[] = {0x2285};
static const unsigned long cp_single_2765[] = {0x0576};
static const unsigned long cp_single_2766[] = {0x24a9};
static const unsigned long cp_single_2767[] = {0x33b1};
static const unsigned long cp_single_2768[] = {0x207f};
static const unsigned long cp_single_2769[] = {0x00f1};
static const unsigned long cp_single_2770[] = {0x03bd};
static const unsigned long cp_single_2771[] = {0x306c};
static const unsigned long cp_single_2772[] = {0x30cc};
static const unsigned long cp_single_2773[] = {0xff87};
static const unsigned long cp_single_2774[] = {0x09bc};
static const unsigned long cp_single_2775[] = {0x093c};
static const unsigned long cp_single_2776[] = {0x0abc};
static const unsigned long cp_single_2777[] = {0x0a3c};
static const unsigned long cp_single_2778[] = {0x0023};
static const unsigned long cp_single_2779[] = {0xff03};
static const unsigned long cp_single_2780[] = {0xfe5f};
static const unsigned long cp_single_2781[] = {0x0374};
static const unsigned long cp_single_2782[] = {0x0375};
static const unsigned long cp_single_2783[] = {0x2116};
static const unsigned long cp_single_2784[] = {0x05e0};
static const unsigned long cp_single_2785[] = {0xfb40};
static const unsigned long cp_single_2786[] = {0xfb40};
static const unsigned long cp_single_2787[] = {0x05e0};
static const unsigned long cp_single_2788[] = {0x33b5};
static const unsigned long cp_single_2789[] = {0x33bb};
static const unsigned long cp_single_2790[] = {0x099e};
static const unsigned long cp_single_2791[] = {0x091e};
static const unsigned long cp_single_2792[] = {0x0a9e};
static const unsigned long cp_single_2793[] = {0x0a1e};
static const unsigned long cp_single_2794[] = {0x006f};
static const unsigned long cp_single_2795[] = {0x00f3};
static const unsigned long cp_single_2796[] = {0x0e2d};
static const unsigned long cp_single_2797[] = {0x0275};
static const unsigned long cp_single_2798[] = {0x04e9};
static const unsigned long cp_single_2799[] = {0x04eb};
static const unsigned long cp_single_2800[] = {0x0993};
static const unsigned long cp_single_2801[] = {0x311b};
static const unsigned long cp_single_2802[] = {0x014f};
static const unsigned long cp_single_2803[] = {0x0911};
static const unsigned long cp_single_2804[] = {0x0a91};
static const unsigned long cp_single_2805[] = {0x0949};
static const unsigned long cp_single_2806[] = {0x0ac9};
static const unsigned long cp_single_2807[] = {0x01d2};
static const unsigned long cp_single_2808[] = {0x24de};
static const unsigned long cp_single_2809[] = {0x00f4};
static const unsigned long cp_single_2810[] = {0x1ed1};
static const unsigned long cp_single_2811[] = {0x1ed9};
static const unsigned long cp_single_2812[] = {0x1ed3};
static const unsigned long cp_single_2813[] = {0x1ed5};
static const unsigned long cp_single_2814[] = {0x1ed7};
static const unsigned long cp_single_2815[] = {0x043e};
static const unsigned long cp_single_2816[] = {0x0151};
static const unsigned long cp_single_2817[] = {0x020d};
static const unsigned long cp_single_2818[] = {0x0913};
static const unsigned long cp_single_2819[] = {0x00f6};
static const unsigned long cp_single_2820[] = {0x04e7};
static const unsigned long cp_single_2821[] = {0x1ecd};
static const unsigned long cp_single_2822[] = {0x0153};
static const unsigned long cp_single_2823[] = {0x315a};
static const unsigned long cp_single_2824[] = {0x02db};
static const unsigned long cp_single_2825[] = {0x0328};
static const unsigned long cp_single_2826[] = {0x00f2};
static const unsigned long cp_single_2827[] = {0x0a93};
static const unsigned long cp_single_2828[] = {0x0585};
static const unsigned long cp_single_2829[] = {0x304a};
static const unsigned long cp_single_2830[] = {0x1ecf};
static const unsigned long cp_single_2831[] = {0x01a1};
static const unsigned long cp_single_2832[] = {0x1edb};
static const unsigned long cp_single_2833[] = {0x1ee3};
static const unsigned long cp_single_2834[] = {0x1edd};
static const unsigned long cp_single_2835[] = {0x1edf};
static const unsigned long cp_single_2836[] = {0x1ee1};
static const unsigned long cp_single_2837[] = {0x0151};
static const unsigned long cp_single_2838[] = {0x01a3};
static const unsigned long cp_single_2839[] = {0x020f};
static const unsigned long cp_single_2840[] = {0x30aa};
static const unsigned long cp_single_2841[] = {0xff75};
static const unsigned long cp_single_2842[] = {0x3157};
static const unsigned long cp_single_2843[] = {0x05ab};
static const unsigned long cp_single_2844[] = {0x014d};
static const unsigned long cp_single_2845[] = {0x1e53};
static const unsigned long cp_single_2846[] = {0x1e51};
static const unsigned long cp_single_2847[] = {0x0950};
static const unsigned long cp_single_2848[] = {0x03c9};
static const unsigned long cp_single_2849[] = {0x03d6};
static const unsigned long cp_single_2850[] = {0x0461};
static const unsigned long cp_single_2851[] = {0x0277};
static const unsigned long cp_single_2852[] = {0x047b};
static const unsigned long cp_single_2853[] = {0x047d};
static const unsigned long cp_single_2854[] = {0x03ce};
static const unsigned long cp_single_2855[] = {0x0ad0};
static const unsigned long cp_single_2856[] = {0x03bf};
static const unsigned long cp_single_2857[] = {0x03cc};
static const unsigned long cp_single_2858[] = {0xff4f};
static const unsigned long cp_single_2859[] = {0x0031};
static const unsigned long cp_single_2860[] = {0x0661};
static const unsigned long cp_single_2861[] = {0x09e7};
static const unsigned long cp_single_2862[] = {0x2460};
static const unsigned long cp_single_2863[] = {0x278a};
static const unsigned long cp_single_2864[] = {0x0967};
static const unsigned long cp_single_2865[] = {0x2024};
static const unsigned long cp_single_2866[] = {0x215b};
static const unsigned long cp_single_2867[] = {0xf6dc};
static const unsigned long cp_single_2868[] = {0x0ae7};
static const unsigned long cp_single_2869[] = {0x0a67};
static const unsigned long cp_single_2870[] = {0x0661};
static const unsigned long cp_single_2871[] = {0x00bd};
static const unsigned long cp_single_2872[] = {0x3021};
static const unsigned long cp_single_2873[] = {0x3220};
static const unsigned long cp_single_2874[] = {0x2081};
static const unsigned long cp_single_2875[] = {0xff11};
static const unsigned long cp_single_2876[] = {0x09f4};
static const unsigned long cp_single_2877[] = {0xf731};
static const unsigned long cp_single_2878[] = {0x2474};
static const unsigned long cp_single_2879[] = {0x2488};
static const unsigned long cp_single_2880[] = {0x06f1};
static const unsigned long cp_single_2881[] = {0x00bc};
static const unsigned long cp_single_2882[] = {0x2170};
static const unsigned long cp_single_2883[] = {0x00b9};
static const unsigned long cp_single_2884[] = {0x0e51};
static const unsigned long cp_single_2885[] = {0x2153};
static const unsigned long cp_single_2886[] = {0x01eb};
static const unsigned long cp_single_2887[] = {0x01ed};
static const unsigned long cp_single_2888[] = {0x0a13};
static const unsigned long cp_single_2889[] = {0x0a4b};
static const unsigned long cp_single_2890[] = {0x0254};
static const unsigned long cp_single_2891[] = {0x24aa};
static const unsigned long cp_single_2892[] = {0x25e6};
static const unsigned long cp_single_2893[] = {0x2325};
static const unsigned long cp_single_2894[] = {0x00aa};
static const unsigned long cp_single_2895[] = {0x00ba};
static const unsigned long cp_single_2896[] = {0x221f};
static const unsigned long cp_single_2897[] = {0x0912};
static const unsigned long cp_single_2898[] = {0x094a};
static const unsigned long cp_single_2899[] = {0x00f8};
static const unsigned long cp_single_2900[] = {0x01ff};
static const unsigned long cp_single_2901[] = {0x3049};
static const unsigned long cp_single_2902[] = {0x30a9};
static const unsigned long cp_single_2903[] = {0xff6b};
static const unsigned long cp_single_2904[] = {0x01ff};
static const unsigned long cp_single_2905[] = {0xf6f0};
static const unsigned long cp_single_2906[] = {0x047f};
static const unsigned long cp_single_2907[] = {0x00f5};
static const unsigned long cp_single_2908[] = {0x1e4d};
static const unsigned long cp_single_2909[] = {0x1e4f};
static const unsigned long cp_single_2910[] = {0x3121};
static const unsigned long cp_single_2911[] = {0x203e};
static const unsigned long cp_single_2912[] = {0xfe4a};
static const unsigned long cp_single_2913[] = {0x0305};
static const unsigned long cp_single_2914[] = {0xfe49};
static const unsigned long cp_single_2915[] = {0xfe4c};
static const unsigned long cp_single_2916[] = {0xfe4b};
static const unsigned long cp_single_2917[] = {0x00af};
static const unsigned long cp_single_2918[] = {0x09cb};
static const unsigned long cp_single_2919[] = {0x094b};
static const unsigned long cp_single_2920[] = {0x0acb};
static const unsigned long cp_single_2921[] = {0x0070};
static const unsigned long cp_single_2922[] = {0x3380};
static const unsigned long cp_single_2923[] = {0x332b};
static const unsigned long cp_single_2924[] = {0x09aa};
static const unsigned long cp_single_2925[] = {0x1e55};
static const unsigned long cp_single_2926[] = {0x092a};
static const unsigned long cp_single_2927[] = {0x21df};
static const unsigned long cp_single_2928[] = {0x21de};
static const unsigned long cp_single_2929[] = {0x0aaa};
static const unsigned long cp_single_2930[] = {0x0a2a};
static const unsigned long cp_single_2931[] = {0x3071};
static const unsigned long cp_single_2932[] = {0x0e2f};
static const unsigned long cp_single_2933[] = {0x30d1};
static const unsigned long cp_single_2934[] = {0x0484};
static const unsigned long cp_single_2935[] = {0x04c0};
static const unsigned long cp_single_2936[] = {0x317f};
static const unsigned long cp_single_2937[] = {0x00b6};
static const unsigned long cp_single_2938[] = {0x2225};
static const unsigned long cp_single_2939[] = {0x0028};
static const unsigned long cp_single_2940[] = {0xfd3e};
static const unsigned long cp_single_2941[] = {0xf8ed};
static const unsigned long cp_single_2942[] = {0xf8ec};
static const unsigned long cp_single_2943[] = {0x208d};
static const unsigned long cp_single_2944[] = {0xff08};
static const unsigned long cp_single_2945[] = {0xfe59};
static const unsigned long cp_single_2946[] = {0x207d};
static const unsigned long cp_single_2947[] = {0xf8eb};
static const unsigned long cp_single_2948[] = {0xfe35};
static const unsigned long cp_single_2949[] = {0x0029};
static const unsigned long cp_single_2950[] = {0xfd3f};
static const unsigned long cp_single_2951[] = {0xf8f8};
static const unsigned long cp_single_2952[] = {0xf8f7};
static const unsigned long cp_single_2953[] = {0x208e};
static const unsigned long cp_single_2954[] = {0xff09};
static const unsigned long cp_single_2955[] = {0xfe5a};
static const unsigned long cp_single_2956[] = {0x207e};
static const unsigned long cp_single_2957[] = {0xf8f6};
static const unsigned long cp_single_2958[] = {0xfe36};
static const unsigned long cp_single_2959[] = {0x2202};
static const unsigned long cp_single_2960[] = {0x05c0};
static const unsigned long cp_single_2961[] = {0x0599};
static const unsigned long cp_single_2962[] = {0x33a9};
static const unsigned long cp_single_2963[] = {0x05b7};
static const unsigned long cp_single_2964[] = {0x05b7};
static const unsigned long cp_single_2965[] = {0x05b7};
static const unsigned long cp_single_2966[] = {0x05b7};
static const unsigned long cp_single_2967[] = {0x05b7};
static const unsigned long cp_single_2968[] = {0x05b7};
static const unsigned long cp_single_2969[] = {0x05b7};
static const unsigned long cp_single_2970[] = {0x05b7};
static const unsigned long cp_single_2971[] = {0x05a1};
static const unsigned long cp_single_2972[] = {0x3106};
static const unsigned long cp_single_2973[] = {0x24df};
static const unsigned long cp_single_2974[] = {0x1e57};
static const unsigned long cp_single_2975[] = {0x05e4};
static const unsigned long cp_single_2976[] = {0x043f};
static const unsigned long cp_single_2977[] = {0xfb44};
static const unsigned long cp_single_2978[] = {0xfb44};
static const unsigned long cp_single_2979[] = {0x333b};
static const unsigned long cp_single_2980[] = {0xfb43};
static const unsigned long cp_single_2981[] = {0x067e};
static const unsigned long cp_single_2982[] = {0x057a};
static const unsigned long cp_single_2983[] = {0x05e4};
static const unsigned long cp_single_2984[] = {0xfb57};
static const unsigned long cp_single_2985[] = {0xfb58};
static const unsigned long cp_single_2986[] = {0x307a};
static const unsigned long cp_single_2987[] = {0xfb59};
static const unsigned long cp_single_2988[] = {0x30da};
static const unsigned long cp_single_2989[] = {0x04a7};
static const unsigned long cp_single_2990[] = {0xfb4e};
static const unsigned long cp_single_2991[] = {0x0025};
static const unsigned long cp_single_2992[] = {0x066a};
static const unsigned long cp_single_2993[] = {0xff05};
static const unsigned long cp_single_2994[] = {0xfe6a};
static const unsigned long cp_single_2995[] = {0x002e};
static const unsigned long cp_single_2996[] = {0x0589};
static const unsigned long cp_single_2997[] = {0x00b7};
static const unsigned long cp_single_2998[] = {0xff61};
static const unsigned long cp_single_2999[] = {0xf6e7};
static const unsigned long cp_single_3000[] = {0xff0e};
static const unsigned long cp_single_3001[] = {0xfe52};
static const unsigned long cp_single_3002[] = {0xf6e8};
static const unsigned long cp_single_3003[] = {0x0342};
static const unsigned long cp_single_3004[] = {0x22a5};
static const unsigned long cp_single_3005[] = {0x2030};
static const unsigned long cp_single_3006[] = {0x20a7};
static const unsigned long cp_single_3007[] = {0x338a};
static const unsigned long cp_single_3008[] = {0x09ab};
static const unsigned long cp_single_3009[] = {0x092b};
static const unsigned long cp_single_3010[] = {0x0aab};
static const unsigned long cp_single_3011[] = {0x0a2b};
static const unsigned long cp_single_3012[] = {0x03c6};
static const unsigned long cp_single_3013[] = {0x03d5};
static const unsigned long cp_single_3014[] = {0x327a};
static const unsigned long cp_single_3015[] = {0x321a};
static const unsigned long cp_single_3016[] = {0x326c};
static const unsigned long cp_single_3017[] = {0x314d};
static const unsigned long cp_single_3018[] = {0x320c};
static const unsigned long cp_single_3019[] = {0x0278};
static const unsigned long cp_single_3020[] = {0x0e3a};
static const unsigned long cp_single_3021[] = {0x03d5};
static const unsigned long cp_single_3022[] = {0x01a5};
static const unsigned long cp_single_3023[] = {0x0e1e};
static const unsigned long cp_single_3024[] = {0x0e1c};
static const unsigned long cp_single_3025[] = {0x0e20};
static const unsigned long cp_single_3026[] = {0x03c0};
static const unsigned long cp_single_3027[] = {0x3273};
static const unsigned long cp_single_3028[] = {0x3213};
static const unsigned long cp_single_3029[] = {0x3176};
static const unsigned long cp_single_3030[] = {0x3265};
static const unsigned long cp_single_3031[] = {0x3172};
static const unsigned long cp_single_3032[] = {0x3142};
static const unsigned long cp_single_3033[] = {0x3205};
static const unsigned long cp_single_3034[] = {0x3174};
static const unsigned long cp_single_3035[] = {0x3144};
static const unsigned long cp_single_3036[] = {0x3175};
static const unsigned long cp_single_3037[] = {0x3177};
static const unsigned long cp_single_3038[] = {0x3173};
static const unsigned long cp_single_3039[] = {0x3074};
static const unsigned long cp_single_3040[] = {0x30d4};
static const unsigned long cp_single_3041[] = {0x03d6};
static const unsigned long cp_single_3042[] = {0x0583};
static const unsigned long cp_single_3043[] = {0x002b};
static const unsigned long cp_single_3044[] = {0x031f};
static const unsigned long cp_single_3045[] = {0x2295};
static const unsigned long cp_single_3046[] = {0x00b1};
static const unsigned long cp_single_3047[] = {0x02d6};
static const unsigned long cp_single_3048[] = {0xff0b};
static const unsigned long cp_single_3049[] = {0xfe62};
static const unsigned long cp_single_3050[] = {0x207a};
static const unsigned long cp_single_3051[] = {0xff50};
static const unsigned long cp_single_3052[] = {0x33d8};
static const unsigned long cp_single_3053[] = {0x307d};
static const unsigned long cp_single_3054[] = {0x261f};
static const unsigned long cp_single_3055[] = {0x261c};
static const unsigned long cp_single_3056[] = {0x261e};
static const unsigned long cp_single_3057[] = {0x261d};
static const unsigned long cp_single_3058[] = {0x30dd};
static const unsigned long cp_single_3059[] = {0x0e1b};
static const unsigned long cp_single_3060[] = {0x3012};
static const unsigned long cp_single_3061[] = {0x3020};
static const unsigned long cp_single_3062[] = {0x24ab};
static const unsigned long cp_single_3063[] = {0x227a};
static const unsigned long cp_single_3064[] = {0x211e};
static const unsigned long cp_single_3065[] = {0x02b9};
static const unsigned long cp_single_3066[] = {0x2035};
static const unsigned long cp_single_3067[] = {0x220f};
static const unsigned long cp_single_3068[] = {0x2305};
static const unsigned long cp_single_3069[] = {0x30fc};
static const unsigned long cp_single_3070[] = {0x2318};
static const unsigned long cp_single_3071[] = {0x2282};
static const unsigned long cp_single_3072[] = {0x2283};
static const unsigned long cp_single_3073[] = {0x2237};
static const unsigned long cp_single_3074[] = {0x221d};
static const unsigned long cp_single_3075[] = {0x03c8};
static const unsigned long cp_single_3076[] = {0x0471};
static const unsigned long cp_single_3077[] = {0x0486};
static const unsigned long cp_single_3078[] = {0x33b0};
static const unsigned long cp_single_3079[] = {0x3077};
static const unsigned long cp_single_3080[] = {0x30d7};
static const unsigned long cp_single_3081[] = {0x33b4};
static const unsigned long cp_single_3082[] = {0x33ba};
static const unsigned long cp_single_3083[] = {0x0071};
static const unsigned long cp_single_3084[] = {0x0958};
static const unsigned long cp_single_3085[] = {0x05a8};
static const unsigned long cp_single_3086[] = {0x0642};
static const unsigned long cp_single_3087[] = {0xfed6};
static const unsigned long cp_single_3088[] = {0xfed7};
static const unsigned long cp_single_3089[] = {0xfed8};
static const unsigned long cp_single_3090[] = {0x05b8};
static const unsigned long cp_single_3091[] = {0x05b8};
static const unsigned long cp_single_3092[] = {0x05b8};
static const unsigned long cp_single_3093[] = {0x05b8};
static const unsigned long cp_single_3094[] = {0x05b8};
static const unsigned long cp_single_3095[] = {0x05b8};
static const unsigned long cp_single_3096[] = {0x05b8};
static const unsigned long cp_single_3097[] = {0x05b8};
static const unsigned long cp_single_3098[] = {0x05b8};
static const unsigned long cp_single_3099[] = {0x05b8};
static const unsigned long cp_single_3100[] = {0x05b8};
static const unsigned long cp_single_3101[] = {0x05b8};
static const unsigned long cp_single_3102[] = {0x05b8};
static const unsigned long cp_single_3103[] = {0x05b8};
static const unsigned long cp_single_3104[] = {0x05b8};
static const unsigned long cp_single_3105[] = {0x05b8};
static const unsigned long cp_single_3106[] = {0x059f};
static const unsigned long cp_single_3107[] = {0x3111};
static const unsigned long cp_single_3108[] = {0x24e0};
static const unsigned long cp_single_3109[] = {0x02a0};
static const unsigned long cp_single_3110[] = {0xff51};
static const unsigned long cp_single_3111[] = {0x05e7};
static const unsigned long cp_single_3112[] = {0xfb47};
static const unsigned long cp_single_3113[] = {0xfb47};
static const unsigned long cp_single_3114[] = {0x05e7};
static const unsigned long cp_single_3115[] = {0x24ac};
static const unsigned long cp_single_3116[] = {0x2669};
static const unsigned long cp_single_3117[] = {0x05bb};
static const unsigned long cp_single_3118[] = {0x05bb};
static const unsigned long cp_single_3119[] = {0x05bb};
static const unsigned long cp_single_3120[] = {0x05bb};
static const unsigned long cp_single_3121[] = {0x05bb};
static const unsigned long cp_single_3122[] = {0x05bb};
static const unsigned long cp_single_3123[] = {0x05bb};
static const unsigned long cp_single_3124[] = {0x05bb};
static const unsigned long cp_single_3125[] = {0x003f};
static const unsigned long cp_single_3126[] = {0x061f};
static const unsigned long cp_single_3127[] = {0x055e};
static const unsigned long cp_single_3128[] = {0x00bf};
static const unsigned long cp_single_3129[] = {0xf7bf};
static const unsigned long cp_single_3130[] = {0x037e};
static const unsigned long cp_single_3131[] = {0xff1f};
static const unsigned long cp_single_3132[] = {0xf73f};
static const unsigned long cp_single_3133[] = {0x0022};
static const unsigned long cp_single_3134[] = {0x201e};
static const unsigned long cp_single_3135[] = {0x201c};
static const unsigned long cp_single_3136[] = {0xff02};
static const unsigned long cp_single_3137[] = {0x301e};
static const unsigned long cp_single_3138[] = {0x301d};
static const unsigned long cp_single_3139[] = {0x201d};
static const unsigned long cp_single_3140[] = {0x2018};
static const unsigned long cp_single_3141[] = {0x201b};
static const unsigned long cp_single_3142[] = {0x201b};
static const unsigned long cp_single_3143[] = {0x2019};
static const unsigned long cp_single_3144[] = {0x0149};
static const unsigned long cp_single_3145[] = {0x201a};
static const unsigned long cp_single_3146[] = {0x0027};
static const unsigned long cp_single_3147[] = {0xff07};
static const unsigned long cp_single_3148[] = {0x0072};
static const unsigned long cp_single_3149[] = {0x057c};
static const unsigned long cp_single_3150[] = {0x09b0};
static const unsigned long cp_single_3151[] = {0x0155};
static const unsigned long cp_single_3152[] = {0x0930};
static const unsigned long cp_single_3153[] = {0x221a};
static const unsigned long cp_single_3154[] = {0xf8e5};
static const unsigned long cp_single_3155[] = {0x33ae};
static const unsigned long cp_single_3156[] = {0x33af};
static const unsigned long cp_single_3157[] = {0x33ad};
static const unsigned long cp_single_3158[] = {0x05bf};
static const unsigned long cp_single_3159[] = {0x05bf};
static const unsigned long cp_single_3160[] = {0x0ab0};
static const unsigned long cp_single_3161[] = {0x0a30};
static const unsigned long cp_single_3162[] = {0x3089};
static const unsigned long cp_single_3163[] = {0x30e9};
static const unsigned long cp_single_3164[] = {0xff97};
static const unsigned long cp_single_3165[] = {0x09f1};
static const unsigned long cp_single_3166[] = {0x09f0};
static const unsigned long cp_single_3167[] = {0x0264};
static const unsigned long cp_single_3168[] = {0x2236};
static const unsigned long cp_single_3169[] = {0x3116};
static const unsigned long cp_single_3170[] = {0x0159};
static const unsigned long cp_single_3171[] = {0x0157};
static const unsigned long cp_single_3172[] = {0x24e1};
static const unsigned long cp_single_3173[] = {0x0157};
static const unsigned long cp_single_3174[] = {0x0211};
static const unsigned long cp_single_3175[] = {0x1e59};
static const unsigned long cp_single_3176[] = {0x1e5b};
static const unsigned long cp_single_3177[] = {0x1e5d};
static const unsigned long cp_single_3178[] = {0x203b};
static const unsigned long cp_single_3179[] = {0x2286};
static const unsigned long cp_single_3180[] = {0x2287};
static const unsigned long cp_single_3181[] = {0x00ae};
static const unsigned long cp_single_3182[] = {0xf8e8};
static const unsigned long cp_single_3183[] = {0xf6da};
static const unsigned long cp_single_3184[] = {0x0631};
static const unsigned long cp_single_3185[] = {0x0580};
static const unsigned long cp_single_3186[] = {0xfeae};
static const unsigned long cp_single_3187[] = {0x308c};
static const unsigned long cp_single_3188[] = {0x30ec};
static const unsigned long cp_single_3189[] = {0xff9a};
static const unsigned long cp_single_3190[] = {0x05e8};
static const unsigned long cp_single_3191[] = {0xfb48};
static const unsigned long cp_single_3192[] = {0x05e8};
static const unsigned long cp_single_3193[] = {0x223d};
static const unsigned long cp_single_3194[] = {0x0597};
static const unsigned long cp_single_3195[] = {0x0597};
static const unsigned long cp_single_3196[] = {0x2310};
static const unsigned long cp_single_3197[] = {0x027e};
static const unsigned long cp_single_3198[] = {0x027f};
static const unsigned long cp_single_3199[] = {0x09dd};
static const unsigned long cp_single_3200[] = {0x095d};
static const unsigned long cp_single_3201[] = {0x03c1};
static const unsigned long cp_single_3202[] = {0x027d};
static const unsigned long cp_single_3203[] = {0x027b};
static const unsigned long cp_single_3204[] = {0x02b5};
static const unsigned long cp_single_3205[] = {0x03f1};
static const unsigned long cp_single_3206[] = {0x02de};
static const unsigned long cp_single_3207[] = {0x3271};
static const unsigned long cp_single_3208[] = {0x3211};
static const unsigned long cp_single_3209[] = {0x3263};
static const unsigned long cp_single_3210[] = {0x3140};
static const unsigned long cp_single_3211[] = {0x313a};
static const unsigned long cp_single_3212[] = {0x3169};
static const unsigned long cp_single_3213[] = {0x3139};
static const unsigned long cp_single_3214[] = {0x313b};
static const unsigned long cp_single_3215[] = {0x316c};
static const unsigned long cp_single_3216[] = {0x3203};
static const unsigned long cp_single_3217[] = {0x313f};
static const unsigned long cp_single_3218[] = {0x313c};
static const unsigned long cp_single_3219[] = {0x316b};
static const unsigned long cp_single_3220[] = {0x313d};
static const unsigned long cp_single_3221[] = {0x313e};
static const unsigned long cp_single_3222[] = {0x316a};
static const unsigned long cp_single_3223[] = {0x316d};
static const unsigned long cp_single_3224[] = {0x221f};
static const unsigned long cp_single_3225[] = {0x0319};
static const unsigned long cp_single_3226[] = {0x22bf};
static const unsigned long cp_single_3227[] = {0x308a};
static const unsigned long cp_single_3228[] = {0x30ea};
static const unsigned long cp_single_3229[] = {0xff98};
static const unsigned long cp_single_3230[] = {0x02da};
static const unsigned long cp_single_3231[] = {0x0325};
static const unsigned long cp_single_3232[] = {0x030a};
static const unsigned long cp_single_3233[] = {0x02bf};
static const unsigned long cp_single_3234[] = {0x0559};
static const unsigned long cp_single_3235[] = {0x031c};
static const unsigned long cp_single_3236[] = {0x02d3};
static const unsigned long cp_single_3237[] = {0x02be};
static const unsigned long cp_single_3238[] = {0x0339};
static const unsigned long cp_single_3239[] = {0x02d2};
static const unsigned long cp_single_3240[] = {0x0213};
static const unsigned long cp_single_3241[] = {0x3351};
static const unsigned long cp_single_3242[] = {0x1e5f};
static const unsigned long cp_single_3243[] = {0x027c};
static const unsigned long cp_single_3244[] = {0x027a};
static const unsigned long cp_single_3245[] = {0xff52};
static const unsigned long cp_single_3246[] = {0x308d};
static const unsigned long cp_single_3247[] = {0x30ed};
static const unsigned long cp_single_3248[] = {0xff9b};
static const unsigned long cp_single_3249[] = {0x0e23};
static const unsigned long cp_single_3250[] = {0x24ad};
static const unsigned long cp_single_3251[] = {0x09dc};
static const unsigned long cp_single_3252[] = {0x0931};
static const unsigned long cp_single_3253[] = {0x0a5c};
static const unsigned long cp_single_3254[] = {0x0691};
static const unsigned long cp_single_3255[] = {0xfb8d};
static const unsigned long cp_single_3256[] = {0x09e0};
static const unsigned long cp_single_3257[] = {0x0960};
static const unsigned long cp_single_3258[] = {0x0ae0};
static const unsigned long cp_single_3259[] = {0x09c4};
static const unsigned long cp_single_3260[] = {0x0944};
static const unsigned long cp_single_3261[] = {0x0ac4};
static const unsigned long cp_single_3262[] = {0xf6f1};
static const unsigned long cp_single_3263[] = {0x2590};
static const unsigned long cp_single_3264[] = {0x0279};
static const unsigned long cp_single_3265[] = {0x02b4};
static const unsigned long cp_single_3266[] = {0x308b};
static const unsigned long cp_single_3267[] = {0x30eb};
static const unsigned long cp_single_3268[] = {0xff99};
static const unsigned long cp_single_3269[] = {0x09f2};
static const unsigned long cp_single_3270[] = {0x09f3};
static const unsigned long cp_single_3271[] = {0xf6dd};
static const unsigned long cp_single_3272[] = {0x0e24};
static const unsigned long cp_single_3273[] = {0x098b};
static const unsigned long cp_single_3274[] = {0x090b};
static const unsigned long cp_single_3275[] = {0x0a8b};
static const unsigned long cp_single_3276[] = {0x09c3};
static const unsigned long cp_single_3277[] = {0x0943};
static const unsigned long cp_single_3278[] = {0x0ac3};
static const unsigned long cp_single_3279[] = {0x0073};
static const unsigned long cp_single_3280[] = {0x09b8};
static const unsigned long cp_single_3281[] = {0x015b};
static const unsigned long cp_single_3282[] = {0x1e65};
static const unsigned long cp_single_3283[] = {0x0635};
static const unsigned long cp_single_3284[] = {0x0938};
static const unsigned long cp_single_3285[] = {0xfeba};
static const unsigned long cp_single_3286[] = {0xfebb};
static const unsigned long cp_single_3287[] = {0xfebc};
static const unsigned long cp_single_3288[] = {0x0ab8};
static const unsigned long cp_single_3289[] = {0x0a38};
static const unsigned long cp_single_3290[] = {0x3055};
static const unsigned long cp_single_3291[] = {0x30b5};
static const unsigned long cp_single_3292[] = {0xff7b};
static const unsigned long cp_single_3293[] = {0xfdfa};
static const unsigned long cp_single_3294[] = {0x05e1};
static const unsigned long cp_single_3295[] = {0xfb41};
static const unsigned long cp_single_3296[] = {0xfb41};
static const unsigned long cp_single_3297[] = {0x05e1};
static const unsigned long cp_single_3298[] = {0x0e32};
static const unsigned long cp_single_3299[] = {0x0e41};
static const unsigned long cp_single_3300[] = {0x0e44};
static const unsigned long cp_single_3301[] = {0x0e43};
static const unsigned long cp_single_3302[] = {0x0e33};
static const unsigned long cp_single_3303[] = {0x0e30};
static const unsigned long cp_single_3304[] = {0x0e40};
static const unsigned long cp_single_3305[] = {0xf886};
static const unsigned long cp_single_3306[] = {0x0e35};
static const unsigned long cp_single_3307[] = {0xf885};
static const unsigned long cp_single_3308[] = {0x0e34};
static const unsigned long cp_single_3309[] = {0x0e42};
static const unsigned long cp_single_3310[] = {0xf888};
static const unsigned long cp_single_3311[] = {0x0e37};
static const unsigned long cp_single_3312[] = {0xf887};
static const unsigned long cp_single_3313[] = {0x0e36};
static const unsigned long cp_single_3314[] = {0x0e38};
static const unsigned long cp_single_3315[] = {0x0e39};
static const unsigned long cp_single_3316[] = {0x3119};
static const unsigned long cp_single_3317[] = {0x0161};
static const unsigned long cp_single_3318[] = {0x1e67};
static const unsigned long cp_single_3319[] = {0x015f};
static const unsigned long cp_single_3320[] = {0x0259};
static const unsigned long cp_single_3321[] = {0x04d9};
static const unsigned long cp_single_3322[] = {0x04db};
static const unsigned long cp_single_3323[] = {0x025a};
static const unsigned long cp_single_3324[] = {0x24e2};
static const unsigned long cp_single_3325[] = {0x015d};
static const unsigned long cp_single_3326[] = {0x0219};
static const unsigned long cp_single_3327[] = {0x1e61};
static const unsigned long cp_single_3328[] = {0x1e63};
static const unsigned long cp_single_3329[] = {0x1e69};
static const unsigned long cp_single_3330[] = {0x033c};
static const unsigned long cp_single_3331[] = {0x2033};
static const unsigned long cp_single_3332[] = {0x02ca};
static const unsigned long cp_single_3333[] = {0x00a7};
static const unsigned long cp_single_3334[] = {0x0633};
static const unsigned long cp_single_3335[] = {0xfeb2};
static const unsigned long cp_single_3336[] = {0xfeb3};
static const unsigned long cp_single_3337[] = {0xfeb4};
static const unsigned long cp_single_3338[] = {0x05b6};
static const unsigned long cp_single_3339[] = {0x05b6};
static const unsigned long cp_single_3340[] = {0x05b6};
static const unsigned long cp_single_3341[] = {0x05b6};
static const unsigned long cp_single_3342[] = {0x05b6};
static const unsigned long cp_single_3343[] = {0x05b6};
static const unsigned long cp_single_3344[] = {0x05b6};
static const unsigned long cp_single_3345[] = {0x0592};
static const unsigned long cp_single_3346[] = {0x05b6};
static const unsigned long cp_single_3347[] = {0x057d};
static const unsigned long cp_single_3348[] = {0x305b};
static const unsigned long cp_single_3349[] = {0x30bb};
static const unsigned long cp_single_3350[] = {0xff7e};
static const unsigned long cp_single_3351[] = {0x003b};
static const unsigned long cp_single_3352[] = {0x061b};
static const unsigned long cp_single_3353[] = {0xff1b};
static const unsigned long cp_single_3354[] = {0xfe54};
static const unsigned long cp_single_3355[] = {0x309c};
static const unsigned long cp_single_3356[] = {0xff9f};
static const unsigned long cp_single_3357[] = {0x3322};
static const unsigned long cp_single_3358[] = {0x3323};
static const unsigned long cp_single_3359[] = {0x0037};
static const unsigned long cp_single_3360[] = {0x0667};
static const unsigned long cp_single_3361[] = {0x09ed};
static const unsigned long cp_single_3362[] = {0x2466};
static const unsigned long cp_single_3363[] = {0x2790};
static const unsigned long cp_single_3364[] = {0x096d};
static const unsigned long cp_single_3365[] = {0x215e};
static const unsigned long cp_single_3366[] = {0x0aed};
static const unsigned long cp_single_3367[] = {0x0a6d};
static const unsigned long cp_single_3368[] = {0x0667};
static const unsigned long cp_single_3369[] = {0x3027};
static const unsigned long cp_single_3370[] = {0x3226};
static const unsigned long cp_single_3371[] = {0x2087};
static const unsigned long cp_single_3372[] = {0xff17};
static const unsigned long cp_single_3373[] = {0xf737};
static const unsigned long cp_single_3374[] = {0x247a};
static const unsigned long cp_single_3375[] = {0x248e};
static const unsigned long cp_single_3376[] = {0x06f7};
static const unsigned long cp_single_3377[] = {0x2176};
static const unsigned long cp_single_3378[] = {0x2077};
static const unsigned long cp_single_3379[] = {0x2470};
static const unsigned long cp_single_3380[] = {0x2484};
static const unsigned long cp_single_3381[] = {0x2498};
static const unsigned long cp_single_3382[] = {0x0e57};
static const unsigned long cp_single_3383[] = {0x00ad};
static const unsigned long cp_single_3384[] = {0x0577};
static const unsigned long cp_single_3385[] = {0x09b6};
static const unsigned long cp_single_3386[] = {0x0448};
static const unsigned long cp_single_3387[] = {0x0651};
static const unsigned long cp_single_3388[] = {0xfc61};
static const unsigned long cp_single_3389[] = {0xfc5e};
static const unsigned long cp_single_3390[] = {0xfc60};
static const unsigned long cp_single_3391[] = {0xfc62};
static const unsigned long cp_single_3392[] = {0xfc5f};
static const unsigned long cp_single_3393[] = {0x2592};
static const unsigned long cp_single_3394[] = {0x2593};
static const unsigned long cp_single_3395[] = {0x2591};
static const unsigned long cp_single_3396[] = {0x2592};
static const unsigned long cp_single_3397[] = {0x0936};
static const unsigned long cp_single_3398[] = {0x0ab6};
static const unsigned long cp_single_3399[] = {0x0a36};
static const unsigned long cp_single_3400[] = {0x0593};
static const unsigned long cp_single_3401[] = {0x3115};
static const unsigned long cp_single_3402[] = {0x0449};
static const unsigned long cp_single_3403[] = {0x0634};
static const unsigned long cp_single_3404[] = {0xfeb6};
static const unsigned long cp_single_3405[] = {0xfeb7};
static const unsigned long cp_single_3406[] = {0xfeb8};
static const unsigned long cp_single_3407[] = {0x03e3};
static const unsigned long cp_single_3408[] = {0x20aa};
static const unsigned long cp_single_3409[] = {0x20aa};
static const unsigned long cp_single_3410[] = {0x05b0};
static const unsigned long cp_single_3411[] = {0x05b0};
static const unsigned long cp_single_3412[] = {0x05b0};
static const unsigned long cp_single_3413[] = {0x05b0};
static const unsigned long cp_single_3414[] = {0x05b0};
static const unsigned long cp_single_3415[] = {0x05b0};
static const unsigned long cp_single_3416[] = {0x05b0};
static const unsigned long cp_single_3417[] = {0x05b0};
static const unsigned long cp_single_3418[] = {0x05b0};
static const unsigned long cp_single_3419[] = {0x04bb};
static const unsigned long cp_single_3420[] = {0x03ed};
static const unsigned long cp_single_3421[] = {0x05e9};
static const unsigned long cp_single_3422[] = {0xfb49};
static const unsigned long cp_single_3423[] = {0xfb49};
static const unsigned long cp_single_3424[] = {0xfb2c};
static const unsigned long cp_single_3425[] = {0xfb2c};
static const unsigned long cp_single_3426[] = {0xfb2d};
static const unsigned long cp_single_3427[] = {0xfb2d};
static const unsigned long cp_single_3428[] = {0x05c1};
static const unsigned long cp_single_3429[] = {0x05e9};
static const unsigned long cp_single_3430[] = {0xfb2a};
static const unsigned long cp_single_3431[] = {0xfb2a};
static const unsigned long cp_single_3432[] = {0xfb2b};
static const unsigned long cp_single_3433[] = {0xfb2b};
static const unsigned long cp_single_3434[] = {0x0282};
static const unsigned long cp_single_3435[] = {0x03c3};
static const unsigned long cp_single_3436[] = {0x03c2};
static const unsigned long cp_single_3437[] = {0x03c2};
static const unsigned long cp_single_3438[] = {0x03f2};
static const unsigned long cp_single_3439[] = {0x3057};
static const unsigned long cp_single_3440[] = {0x30b7};
static const unsigned long cp_single_3441[] = {0xff7c};
static const unsigned long cp_single_3442[] = {0x05bd};
static const unsigned long cp_single_3443[] = {0x05bd};
static const unsigned long cp_single_3444[] = {0x223c};
static const unsigned long cp_single_3445[] = {0x05c2};
static const unsigned long cp_single_3446[] = {0x3274};
static const unsigned long cp_single_3447[] = {0x3214};
static const unsigned long cp_single_3448[] = {0x317e};
static const unsigned long cp_single_3449[] = {0x3266};
static const unsigned long cp_single_3450[] = {0x317a};
static const unsigned long cp_single_3451[] = {0x3145};
static const unsigned long cp_single_3452[] = {0x317b};
static const unsigned long cp_single_3453[] = {0x3206};
static const unsigned long cp_single_3454[] = {0x317d};
static const unsigned long cp_single_3455[] = {0x317c};
static const unsigned long cp_single_3456[] = {0x0036};
static const unsigned long cp_single_3457[] = {0x0666};
static const unsigned long cp_single_3458[] = {0x09ec};
static const unsigned long cp_single_3459[] = {0x2465};
static const unsigned long cp_single_3460[] = {0x278f};
static const unsigned long cp_single_3461[] = {0x096c};
static const unsigned long cp_single_3462[] = {0x0aec};
static const unsigned long cp_single_3463[] = {0x0a6c};
static const unsigned long cp_single_3464[] = {0x0666};
static const unsigned long cp_single_3465[] = {0x3026};
static const unsigned long cp_single_3466[] = {0x3225};
static const unsigned long cp_single_3467[] = {0x2086};
static const unsigned long cp_single_3468[] = {0xff16};
static const unsigned long cp_single_3469[] = {0xf736};
static const unsigned long cp_single_3470[] = {0x2479};
static const unsigned long cp_single_3471[] = {0x248d};
static const unsigned long cp_single_3472[] = {0x06f6};
static const unsigned long cp_single_3473[] = {0x2175};
static const unsigned long cp_single_3474[] = {0x2076};
static const unsigned long cp_single_3475[] = {0x246f};
static const unsigned long cp_single_3476[] = {0x09f9};
static const unsigned long cp_single_3477[] = {0x2483};
static const unsigned long cp_single_3478[] = {0x2497};
static const unsigned long cp_single_3479[] = {0x0e56};
static const unsigned long cp_single_3480[] = {0x002f};
static const unsigned long cp_single_3481[] = {0xff0f};
static const unsigned long cp_single_3482[] = {0x017f};
static const unsigned long cp_single_3483[] = {0x1e9b};
static const unsigned long cp_single_3484[] = {0x263a};
static const unsigned long cp_single_3485[] = {0xff53};
static const unsigned long cp_single_3486[] = {0x05c3};
static const unsigned long cp_single_3487[] = {0x00ad};
static const unsigned long cp_single_3488[] = {0x044c};
static const unsigned long cp_single_3489[] = {0x305d};
static const unsigned long cp_single_3490[] = {0x30bd};
static const unsigned long cp_single_3491[] = {0xff7f};
static const unsigned long cp_single_3492[] = {0x0338};
static const unsigned long cp_single_3493[] = {0x0337};
static const unsigned long cp_single_3494[] = {0x0e29};
static const unsigned long cp_single_3495[] = {0x0e28};
static const unsigned long cp_single_3496[] = {0x0e0b};
static const unsigned long cp_single_3497[] = {0x0e2a};
static const unsigned long cp_single_3498[] = {0x0020};
static const unsigned long cp_single_3499[] = {0x0020};
static const unsigned long cp_single_3500[] = {0x2660};
static const unsigned long cp_single_3501[] = {0x2660};
static const unsigned long cp_single_3502[] = {0x2664};
static const unsigned long cp_single_3503[] = {0x24ae};
static const unsigned long cp_single_3504[] = {0x033b};
static const unsigned long cp_single_3505[] = {0x33c4};
static const unsigned long cp_single_3506[] = {0x339d};
static const unsigned long cp_single_3507[] = {0x25a9};
static const unsigned long cp_single_3508[] = {0x25a4};
static const unsigned long cp_single_3509[] = {0x338f};
static const unsigned long cp_single_3510[] = {0x339e};
static const unsigned long cp_single_3511[] = {0x33ce};
static const unsigned long cp_single_3512[] = {0x33d1};
static const unsigned long cp_single_3513[] = {0x33d2};
static const unsigned long cp_single_3514[] = {0x338e};
static const unsigned long cp_single_3515[] = {0x33d5};
static const unsigned long cp_single_3516[] = {0x339c};
static const unsigned long cp_single_3517[] = {0x33a1};
static const unsigned long cp_single_3518[] = {0x25a6};
static const unsigned long cp_single_3519[] = {0x25a7};
static const unsigned long cp_single_3520[] = {0x25a8};
static const unsigned long cp_single_3521[] = {0x25a5};
static const unsigned long cp_single_3522[] = {0x25a3};
static const unsigned long cp_single_3523[] = {0x33db};
static const unsigned long cp_single_3524[] = {0x09b7};
static const unsigned long cp_single_3525[] = {0x0937};
static const unsigned long cp_single_3526[] = {0x0ab7};
static const unsigned long cp_single_3527[] = {0x3149};
static const unsigned long cp_single_3528[] = {0x3185};
static const unsigned long cp_single_3529[] = {0x3180};
static const unsigned long cp_single_3530[] = {0x3132};
static const unsigned long cp_single_3531[] = {0x3165};
static const unsigned long cp_single_3532[] = {0x3143};
static const unsigned long cp_single_3533[] = {0x3146};
static const unsigned long cp_single_3534[] = {0x3138};
static const unsigned long cp_single_3535[] = {0xf6f2};
static const unsigned long cp_single_3536[] = {0x00a3};
static const unsigned long cp_single_3537[] = {0xffe1};
static const unsigned long cp_single_3538[] = {0x0336};
static const unsigned long cp_single_3539[] = {0x0335};
static const unsigned long cp_single_3540[] = {0x2282};
static const unsigned long cp_single_3541[] = {0x228a};
static const unsigned long cp_single_3542[] = {0x2286};
static const unsigned long cp_single_3543[] = {0x227b};
static const unsigned long cp_single_3544[] = {0x220b};
static const unsigned long cp_single_3545[] = {0x3059};
static const unsigned long cp_single_3546[] = {0x30b9};
static const unsigned long cp_single_3547[] = {0xff7d};
static const unsigned long cp_single_3548[] = {0x0652};
static const unsigned long cp_single_3549[] = {0x2211};
static const unsigned long cp_single_3550[] = {0x263c};
static const unsigned long cp_single_3551[] = {0x2283};
static const unsigned long cp_single_3552[] = {0x228b};
static const unsigned long cp_single_3553[] = {0x2287};
static const unsigned long cp_single_3554[] = {0x33dc};
static const unsigned long cp_single_3555[] = {0x337c};
static const unsigned long cp_single_3556[] = {0x0074};
static const unsigned long cp_single_3557[] = {0x09a4};
static const unsigned long cp_single_3558[] = {0x22a4};
static const unsigned long cp_single_3559[] = {0x22a3};
static const unsigned long cp_single_3560[] = {0x0924};
static const unsigned long cp_single_3561[] = {0x0aa4};
static const unsigned long cp_single_3562[] = {0x0a24};
static const unsigned long cp_single_3563[] = {0x0637};
static const unsigned long cp_single_3564[] = {0xfec2};
static const unsigned long cp_single_3565[] = {0xfec3};
static const unsigned long cp_single_3566[] = {0x305f};
static const unsigned long cp_single_3567[] = {0xfec4};
static const unsigned long cp_single_3568[] = {0x337d};
static const unsigned long cp_single_3569[] = {0x30bf};
static const unsigned long cp_single_3570[] = {0xff80};
static const unsigned long cp_single_3571[] = {0x0640};
static const unsigned long cp_single_3572[] = {0x03c4};
static const unsigned long cp_single_3573[] = {0x05ea};
static const unsigned long cp_single_3574[] = {0xfb4a};
static const unsigned long cp_single_3575[] = {0xfb4a};
static const unsigned long cp_single_3576[] = {0xfb4a};
static const unsigned long cp_single_3577[] = {0x05ea};
static const unsigned long cp_single_3578[] = {0x0167};
static const unsigned long cp_single_3579[] = {0x310a};
static const unsigned long cp_single_3580[] = {0x0165};
static const unsigned long cp_single_3581[] = {0x02a8};
static const unsigned long cp_single_3582[] = {0x0163};
static const unsigned long cp_single_3583[] = {0x0686};
static const unsigned long cp_single_3584[] = {0xfb7b};
static const unsigned long cp_single_3585[] = {0xfb7c};
static const unsigned long cp_single_3586[] = {0xfb7d};
static const unsigned long cp_single_3587[] = {0x24e3};
static const unsigned long cp_single_3588[] = {0x1e71};
static const unsigned long cp_single_3589[] = {0x0163};
static const unsigned long cp_single_3590[] = {0x1e97};
static const unsigned long cp_single_3591[] = {0x1e6b};
static const unsigned long cp_single_3592[] = {0x1e6d};
static const unsigned long cp_single_3593[] = {0x0442};
static const unsigned long cp_single_3594[] = {0x04ad};
static const unsigned long cp_single_3595[] = {0x062a};
static const unsigned long cp_single_3596[] = {0xfe96};
static const unsigned long cp_single_3597[] = {0xfca2};
static const unsigned long cp_single_3598[] = {0xfc0c};
static const unsigned long cp_single_3599[] = {0xfe97};
static const unsigned long cp_single_3600[] = {0x3066};
static const unsigned long cp_single_3601[] = {0xfca1};
static const unsigned long cp_single_3602[] = {0xfc0b};
static const unsigned long cp_single_3603[] = {0x0629};
static const unsigned long cp_single_3604[] = {0xfe94};
static const unsigned long cp_single_3605[] = {0xfe98};
static const unsigned long cp_single_3606[] = {0xfca4};
static const unsigned long cp_single_3607[] = {0xfc0e};
static const unsigned long cp_single_3608[] = {0xfc73};
static const unsigned long cp_single_3609[] = {0x30c6};
static const unsigned long cp_single_3610[] = {0xff83};
static const unsigned long cp_single_3611[] = {0x2121};
static const unsigned long cp_single_3612[] = {0x260e};
static const unsigned long cp_single_3613[] = {0x05a0};
static const unsigned long cp_single_3614[] = {0x05a9};
static const unsigned long cp_single_3615[] = {0x2469};
static const unsigned long cp_single_3616[] = {0x3229};
static const unsigned long cp_single_3617[] = {0x247d};
static const unsigned long cp_single_3618[] = {0x2491};
static const unsigned long cp_single_3619[] = {0x2179};
static const unsigned long cp_single_3620[] = {0x02a7};
static const unsigned long cp_single_3621[] = {0x05d8};
static const unsigned long cp_single_3622[] = {0xfb38};
static const unsigned long cp_single_3623[] = {0xfb38};
static const unsigned long cp_single_3624[] = {0x05d8};
static const unsigned long cp_single_3625[] = {0x04b5};
static const unsigned long cp_single_3626[] = {0x059b};
static const unsigned long cp_single_3627[] = {0x059b};
static const unsigned long cp_single_3628[] = {0x09a5};
static const unsigned long cp_single_3629[] = {0x0925};
static const unsigned long cp_single_3630[] = {0x0aa5};
static const unsigned long cp_single_3631[] = {0x0a25};
static const unsigned long cp_single_3632[] = {0x0630};
static const unsigned long cp_single_3633[] = {0xfeac};
static const unsigned long cp_single_3634[] = {0xf898};
static const unsigned long cp_single_3635[] = {0xf897};
static const unsigned long cp_single_3636[] = {0x0e4c};
static const unsigned long cp_single_3637[] = {0xf896};
static const unsigned long cp_single_3638[] = {0x062b};
static const unsigned long cp_single_3639[] = {0xfe9a};
static const unsigned long cp_single_3640[] = {0xfe9b};
static const unsigned long cp_single_3641[] = {0xfe9c};
static const unsigned long cp_single_3642[] = {0x2203};
static const unsigned long cp_single_3643[] = {0x2234};
static const unsigned long cp_single_3644[] = {0x03b8};
static const unsigned long cp_single_3645[] = {0x03d1};
static const unsigned long cp_single_3646[] = {0x03d1};
static const unsigned long cp_single_3647[] = {0x3279};
static const unsigned long cp_single_3648[] = {0x3219};
static const unsigned long cp_single_3649[] = {0x326b};
static const unsigned long cp_single_3650[] = {0x314c};
static const unsigned long cp_single_3651[] = {0x320b};
static const unsigned long cp_single_3652[] = {0x246c};
static const unsigned long cp_single_3653[] = {0x2480};
static const unsigned long cp_single_3654[] = {0x2494};
static const unsigned long cp_single_3655[] = {0x0e11};
static const unsigned long cp_single_3656[] = {0x01ad};
static const unsigned long cp_single_3657[] = {0x0e12};
static const unsigned long cp_single_3658[] = {0x00fe};
static const unsigned long cp_single_3659[] = {0x0e17};
static const unsigned long cp_single_3660[] = {0x0e10};
static const unsigned long cp_single_3661[] = {0x0e18};
static const unsigned long cp_single_3662[] = {0x0e16};
static const unsigned long cp_single_3663[] = {0x0482};
static const unsigned long cp_single_3664[] = {0x066c};
static const unsigned long cp_single_3665[] = {0x066c};
static const unsigned long cp_single_3666[] = {0x0033};
static const unsigned long cp_single_3667[] = {0x0663};
static const unsigned long cp_single_3668[] = {0x09e9};
static const unsigned long cp_single_3669[] = {0x2462};
static const unsigned long cp_single_3670[] = {0x278c};
static const unsigned long cp_single_3671[] = {0x0969};
static const unsigned long cp_single_3672[] = {0x215c};
static const unsigned long cp_single_3673[] = {0x0ae9};
static const unsigned long cp_single_3674[] = {0x0a69};
static const unsigned long cp_single_3675[] = {0x0663};
static const unsigned long cp_single_3676[] = {0x3023};
static const unsigned long cp_single_3677[] = {0x3222};
static const unsigned long cp_single_3678[] = {0x2083};
static const unsigned long cp_single_3679[] = {0xff13};
static const unsigned long cp_single_3680[] = {0x09f6};
static const unsigned long cp_single_3681[] = {0xf733};
static const unsigned long cp_single_3682[] = {0x2476};
static const unsigned long cp_single_3683[] = {0x248a};
static const unsigned long cp_single_3684[] = {0x06f3};
static const unsigned long cp_single_3685[] = {0x00be};
static const unsigned long cp_single_3686[] = {0xf6de};
static const unsigned long cp_single_3687[] = {0x2172};
static const unsigned long cp_single_3688[] = {0x00b3};
static const unsigned long cp_single_3689[] = {0x0e53};
static const unsigned long cp_single_3690[] = {0x3394};
static const unsigned long cp_single_3691[] = {0x3061};
static const unsigned long cp_single_3692[] = {0x30c1};
static const unsigned long cp_single_3693[] = {0xff81};
static const unsigned long cp_single_3694[] = {0x3270};
static const unsigned long cp_single_3695[] = {0x3210};
static const unsigned long cp_single_3696[] = {0x3262};
static const unsigned long cp_single_3697[] = {0x3137};
static const unsigned long cp_single_3698[] = {0x3202};
static const unsigned long cp_single_3699[] = {0x02dc};
static const unsigned long cp_single_3700[] = {0x0330};
static const unsigned long cp_single_3701[] = {0x0303};
static const unsigned long cp_single_3702[] = {0x0303};
static const unsigned long cp_single_3703[] = {0x0360};
static const unsigned long cp_single_3704[] = {0x223c};
static const unsigned long cp_single_3705[] = {0x0334};
static const unsigned long cp_single_3706[] = {0x033e};
static const unsigned long cp_single_3707[] = {0x2297};
static const unsigned long cp_single_3708[] = {0x0596};
static const unsigned long cp_single_3709[] = {0x0596};
static const unsigned long cp_single_3710[] = {0x0a70};
static const unsigned long cp_single_3711[] = {0x0483};
static const unsigned long cp_single_3712[] = {0x057f};
static const unsigned long cp_single_3713[] = {0x1e6f};
static const unsigned long cp_single_3714[] = {0xff54};
static const unsigned long cp_single_3715[] = {0x0569};
static const unsigned long cp_single_3716[] = {0x3068};
static const unsigned long cp_single_3717[] = {0x30c8};
static const unsigned long cp_single_3718[] = {0xff84};
static const unsigned long cp_single_3719[] = {0x02e5};
static const unsigned long cp_single_3720[] = {0x02e9};
static const unsigned long cp_single_3721[] = {0x02e6};
static const unsigned long cp_single_3722[] = {0x02e8};
static const unsigned long cp_single_3723[] = {0x02e7};
static const unsigned long cp_single_3724[] = {0x01bd};
static const unsigned long cp_single_3725[] = {0x0185};
static const unsigned long cp_single_3726[] = {0x01a8};
static const unsigned long cp_single_3727[] = {0x0384};
static const unsigned long cp_single_3728[] = {0x3327};
static const unsigned long cp_single_3729[] = {0x0e0f};
static const unsigned long cp_single_3730[] = {0x3014};
static const unsigned long cp_single_3731[] = {0xfe5d};
static const unsigned long cp_single_3732[] = {0xfe39};
static const unsigned long cp_single_3733[] = {0x3015};
static const unsigned long cp_single_3734[] = {0xfe5e};
static const unsigned long cp_single_3735[] = {0xfe3a};
static const unsigned long cp_single_3736[] = {0x0e15};
static const unsigned long cp_single_3737[] = {0x01ab};
static const unsigned long cp_single_3738[] = {0x24af};
static const unsigned long cp_single_3739[] = {0x2122};
static const unsigned long cp_single_3740[] = {0xf8ea};
static const unsigned long cp_single_3741[] = {0xf6db};
static const unsigned long cp_single_3742[] = {0x0288};
static const unsigned long cp_single_3743[] = {0x25bc};
static const unsigned long cp_single_3744[] = {0x25c4};
static const unsigned long cp_single_3745[] = {0x25ba};
static const unsigned long cp_single_3746[] = {0x25b2};
static const unsigned long cp_single_3747[] = {0x02a6};
static const unsigned long cp_single_3748[] = {0x05e6};
static const unsigned long cp_single_3749[] = {0xfb46};
static const unsigned long cp_single_3750[] = {0xfb46};
static const unsigned long cp_single_3751[] = {0x05e6};
static const unsigned long cp_single_3752[] = {0x0446};
static const unsigned long cp_single_3753[] = {0x05b5};
static const unsigned long cp_single_3754[] = {0x05b5};
static const unsigned long cp_single_3755[] = {0x05b5};
static const unsigned long cp_single_3756[] = {0x05b5};
static const unsigned long cp_single_3757[] = {0x05b5};
static const unsigned long cp_single_3758[] = {0x05b5};
static const unsigned long cp_single_3759[] = {0x05b5};
static const unsigned long cp_single_3760[] = {0x05b5};
static const unsigned long cp_single_3761[] = {0x045b};
static const unsigned long cp_single_3762[] = {0xf6f3};
static const unsigned long cp_single_3763[] = {0x099f};
static const unsigned long cp_single_3764[] = {0x091f};
static const unsigned long cp_single_3765[] = {0x0a9f};
static const unsigned long cp_single_3766[] = {0x0a1f};
static const unsigned long cp_single_3767[] = {0x0679};
static const unsigned long cp_single_3768[] = {0xfb67};
static const unsigned long cp_single_3769[] = {0xfb68};
static const unsigned long cp_single_3770[] = {0xfb69};
static const unsigned long cp_single_3771[] = {0x09a0};
static const unsigned long cp_single_3772[] = {0x0920};
static const unsigned long cp_single_3773[] = {0x0aa0};
static const unsigned long cp_single_3774[] = {0x0a20};
static const unsigned long cp_single_3775[] = {0x0287};
static const unsigned long cp_single_3776[] = {0x3064};
static const unsigned long cp_single_3777[] = {0x30c4};
static const unsigned long cp_single_3778[] = {0xff82};
static const unsigned long cp_single_3779[] = {0x3063};
static const unsigned long cp_single_3780[] = {0x30c3};
static const unsigned long cp_single_3781[] = {0xff6f};
static const unsigned long cp_single_3782[] = {0x246b};
static const unsigned long cp_single_3783[] = {0x247f};
static const unsigned long cp_single_3784[] = {0x2493};
static const unsigned long cp_single_3785[] = {0x217b};
static const unsigned long cp_single_3786[] = {0x2473};
static const unsigned long cp_single_3787[] = {0x5344};
static const unsigned long cp_single_3788[] = {0x2487};
static const unsigned long cp_single_3789[] = {0x249b};
static const unsigned long cp_single_3790[] = {0x0032};
static const unsigned long cp_single_3791[] = {0x0662};
static const unsigned long cp_single_3792[] = {0x09e8};
static const unsigned long cp_single_3793[] = {0x2461};
static const unsigned long cp_single_3794[] = {0x278b};
static const unsigned long cp_single_3795[] = {0x0968};
static const unsigned long cp_single_3796[] = {0x2025};
static const unsigned long cp_single_3797[] = {0x2025};
static const unsigned long cp_single_3798[] = {0xfe30};
static const unsigned long cp_single_3799[] = {0x0ae8};
static const unsigned long cp_single_3800[] = {0x0a68};
static const unsigned long cp_single_3801[] = {0x0662};
static const unsigned long cp_single_3802[] = {0x3022};
static const unsigned long cp_single_3803[] = {0x3221};
static const unsigned long cp_single_3804[] = {0x2082};
static const unsigned long cp_single_3805[] = {0xff12};
static const unsigned long cp_single_3806[] = {0x09f5};
static const unsigned long cp_single_3807[] = {0xf732};
static const unsigned long cp_single_3808[] = {0x2475};
static const unsigned long cp_single_3809[] = {0x2489};
static const unsigned long cp_single_3810[] = {0x06f2};
static const unsigned long cp_single_3811[] = {0x2171};
static const unsigned long cp_single_3812[] = {0x01bb};
static const unsigned long cp_single_3813[] = {0x00b2};
static const unsigned long cp_single_3814[] = {0x0e52};
static const unsigned long cp_single_3815[] = {0x2154};
static const unsigned long cp_single_3816[] = {0x0075};
static const unsigned long cp_single_3817[] = {0x00fa};
static const unsigned long cp_single_3818[] = {0x0289};
static const unsigned long cp_single_3819[] = {0x0989};
static const unsigned long cp_single_3820[] = {0x3128};
static const unsigned long cp_single_3821[] = {0x016d};
static const unsigned long cp_single_3822[] = {0x01d4};
static const unsigned long cp_single_3823[] = {0x24e4};
static const unsigned long cp_single_3824[] = {0x00fb};
static const unsigned long cp_single_3825[] = {0x1e77};
static const unsigned long cp_single_3826[] = {0x0443};
static const unsigned long cp_single_3827[] = {0x0951};
static const unsigned long cp_single_3828[] = {0x0171};
static const unsigned long cp_single_3829[] = {0x0215};
static const unsigned long cp_single_3830[] = {0x0909};
static const unsigned long cp_single_3831[] = {0x00fc};
static const unsigned long cp_single_3832[] = {0x01d8};
static const unsigned long cp_single_3833[] = {0x1e73};
static const unsigned long cp_single_3834[] = {0x01da};
static const unsigned long cp_single_3835[] = {0x04f1};
static const unsigned long cp_single_3836[] = {0x01dc};
static const unsigned long cp_single_3837[] = {0x01d6};
static const unsigned long cp_single_3838[] = {0x1ee5};
static const unsigned long cp_single_3839[] = {0x00f9};
static const unsigned long cp_single_3840[] = {0x0a89};
static const unsigned long cp_single_3841[] = {0x0a09};
static const unsigned long cp_single_3842[] = {0x3046};
static const unsigned long cp_single_3843[] = {0x1ee7};
static const unsigned long cp_single_3844[] = {0x01b0};
static const unsigned long cp_single_3845[] = {0x1ee9};
static const unsigned long cp_single_3846[] = {0x1ef1};
static const unsigned long cp_single_3847[] = {0x1eeb};
static const unsigned long cp_single_3848[] = {0x1eed};
static const unsigned long cp_single_3849[] = {0x1eef};
static const unsigned long cp_single_3850[] = {0x0171};
static const unsigned long cp_single_3851[] = {0x04f3};
static const unsigned long cp_single_3852[] = {0x0217};
static const unsigned long cp_single_3853[] = {0x30a6};
static const unsigned long cp_single_3854[] = {0xff73};
static const unsigned long cp_single_3855[] = {0x0479};
static const unsigned long cp_single_3856[] = {0x315c};
static const unsigned long cp_single_3857[] = {0x016b};
static const unsigned long cp_single_3858[] = {0x04ef};
static const unsigned long cp_single_3859[] = {0x1e7b};
static const unsigned long cp_single_3860[] = {0x0a41};
static const unsigned long cp_single_3861[] = {0xff55};
static const unsigned long cp_single_3862[] = {0x005f};
static const unsigned long cp_single_3863[] = {0x2017};
static const unsigned long cp_single_3864[] = {0xff3f};
static const unsigned long cp_single_3865[] = {0xfe33};
static const unsigned long cp_single_3866[] = {0xfe4f};
static const unsigned long cp_single_3867[] = {0x222a};
static const unsigned long cp_single_3868[] = {0x2200};
static const unsigned long cp_single_3869[] = {0x0173};
static const unsigned long cp_single_3870[] = {0x24b0};
static const unsigned long cp_single_3871[] = {0x2580};
static const unsigned long cp_single_3872[] = {0x05c4};
static const unsigned long cp_single_3873[] = {0x03c5};
static const unsigned long cp_single_3874[] = {0x03cb};
static const unsigned long cp_single_3875[] = {0x03b0};
static const unsigned long cp_single_3876[] = {0x028a};
static const unsigned long cp_single_3877[] = {0x03cd};
static const unsigned long cp_single_3878[] = {0x031d};
static const unsigned long cp_single_3879[] = {0x02d4};
static const unsigned long cp_single_3880[] = {0x0a73};
static const unsigned long cp_single_3881[] = {0x016f};
static const unsigned long cp_single_3882[] = {0x045e};
static const unsigned long cp_single_3883[] = {0x3045};
static const unsigned long cp_single_3884[] = {0x30a5};
static const unsigned long cp_single_3885[] = {0xff69};
static const unsigned long cp_single_3886[] = {0x04af};
static const unsigned long cp_single_3887[] = {0x04b1};
static const unsigned long cp_single_3888[] = {0x0169};
static const unsigned long cp_single_3889[] = {0x1e79};
static const unsigned long cp_single_3890[] = {0x1e75};
static const unsigned long cp_single_3891[] = {0x098a};
static const unsigned long cp_single_3892[] = {0x090a};
static const unsigned long cp_single_3893[] = {0x0a8a};
static const unsigned long cp_single_3894[] = {0x0a0a};
static const unsigned long cp_single_3895[] = {0x0a42};
static const unsigned long cp_single_3896[] = {0x09c2};
static const unsigned long cp_single_3897[] = {0x0942};
static const unsigned long cp_single_3898[] = {0x0ac2};
static const unsigned long cp_single_3899[] = {0x09c1};
static const unsigned long cp_single_3900[] = {0x0941};
static const unsigned long cp_single_3901[] = {0x0ac1};
static const unsigned long cp_single_3902[] = {0x0076};
static const unsigned long cp_single_3903[] = {0x0935};
static const unsigned long cp_single_3904[] = {0x0ab5};
static const unsigned long cp_single_3905[] = {0x0a35};
static const unsigned long cp_single_3906[] = {0x30f7};
static const unsigned long cp_single_3907[] = {0x05d5};
static const unsigned long cp_single_3908[] = {0xfb35};
static const unsigned long cp_single_3909[] = {0xfb35};
static const unsigned long cp_single_3910[] = {0xfb35};
static const unsigned long cp_single_3911[] = {0x05d5};
static const unsigned long cp_single_3912[] = {0xfb4b};
static const unsigned long cp_single_3913[] = {0xfb4b};
static const unsigned long cp_single_3914[] = {0x05f0};
static const unsigned long cp_single_3915[] = {0x05f1};
static const unsigned long cp_single_3916[] = {0x24e5};
static const unsigned long cp_single_3917[] = {0x1e7f};
static const unsigned long cp_single_3918[] = {0x0432};
static const unsigned long cp_single_3919[] = {0x06a4};
static const unsigned long cp_single_3920[] = {0xfb6b};
static const unsigned long cp_single_3921[] = {0xfb6c};
static const unsigned long cp_single_3922[] = {0xfb6d};
static const unsigned long cp_single_3923[] = {0x30f9};
static const unsigned long cp_single_3924[] = {0x2640};
static const unsigned long cp_single_3925[] = {0x007c};
static const unsigned long cp_single_3926[] = {0x030d};
static const unsigned long cp_single_3927[] = {0x0329};
static const unsigned long cp_single_3928[] = {0x02cc};
static const unsigned long cp_single_3929[] = {0x02c8};
static const unsigned long cp_single_3930[] = {0x057e};
static const unsigned long cp_single_3931[] = {0x028b};
static const unsigned long cp_single_3932[] = {0x30f8};
static const unsigned long cp_single_3933[] = {0x09cd};
static const unsigned long cp_single_3934[] = {0x094d};
static const unsigned long cp_single_3935[] = {0x0acd};
static const unsigned long cp_single_3936[] = {0x0983};
static const unsigned long cp_single_3937[] = {0x0903};
static const unsigned long cp_single_3938[] = {0x0a83};
static const unsigned long cp_single_3939[] = {0xff56};
static const unsigned long cp_single_3940[] = {0x0578};
static const unsigned long cp_single_3941[] = {0x309e};
static const unsigned long cp_single_3942[] = {0x30fe};
static const unsigned long cp_single_3943[] = {0x309b};
static const unsigned long cp_single_3944[] = {0xff9e};
static const unsigned long cp_single_3945[] = {0x30fa};
static const unsigned long cp_single_3946[] = {0x24b1};
static const unsigned long cp_single_3947[] = {0x1e7d};
static const unsigned long cp_single_3948[] = {0x028c};
static const unsigned long cp_single_3949[] = {0x3094};
static const unsigned long cp_single_3950[] = {0x30f4};
static const unsigned long cp_single_3951[] = {0x0077};
static const unsigned long cp_single_3952[] = {0x1e83};
static const unsigned long cp_single_3953[] = {0x3159};
static const unsigned long cp_single_3954[] = {0x308f};
static const unsigned long cp_single_3955[] = {0x30ef};
static const unsigned long cp_single_3956[] = {0xff9c};
static const unsigned long cp_single_3957[] = {0x3158};
static const unsigned long cp_single_3958[] = {0x308e};
static const unsigned long cp_single_3959[] = {0x30ee};
static const unsigned long cp_single_3960[] = {0x3357};
static const unsigned long cp_single_3961[] = {0x301c};
static const unsigned long cp_single_3962[] = {0xfe34};
static const unsigned long cp_single_3963[] = {0x0648};
static const unsigned long cp_single_3964[] = {0xfeee};
static const unsigned long cp_single_3965[] = {0x0624};
static const unsigned long cp_single_3966[] = {0xfe86};
static const unsigned long cp_single_3967[] = {0x33dd};
static const unsigned long cp_single_3968[] = {0x24e6};
static const unsigned long cp_single_3969[] = {0x0175};
static const unsigned long cp_single_3970[] = {0x1e85};
static const unsigned long cp_single_3971[] = {0x1e87};
static const unsigned long cp_single_3972[] = {0x1e89};
static const unsigned long cp_single_3973[] = {0x3091};
static const unsigned long cp_single_3974[] = {0x2118};
static const unsigned long cp_single_3975[] = {0x30f1};
static const unsigned long cp_single_3976[] = {0x315e};
static const unsigned long cp_single_3977[] = {0x315d};
static const unsigned long cp_single_3978[] = {0x1e81};
static const unsigned long cp_single_3979[] = {0x25e6};
static const unsigned long cp_single_3980[] = {0x25cb};
static const unsigned long cp_single_3981[] = {0x25d9};
static const unsigned long cp_single_3982[] = {0x300e};
static const unsigned long cp_single_3983[] = {0xfe43};
static const unsigned long cp_single_3984[] = {0x300f};
static const unsigned long cp_single_3985[] = {0xfe44};
static const unsigned long cp_single_3986[] = {0x25c7};
static const unsigned long cp_single_3987[] = {0x25c8};
static const unsigned long cp_single_3988[] = {0x25bf};
static const unsigned long cp_single_3989[] = {0x25bd};
static const unsigned long cp_single_3990[] = {0x25c3};
static const unsigned long cp_single_3991[] = {0x25c1};
static const unsigned long cp_single_3992[] = {0x3016};
static const unsigned long cp_single_3993[] = {0x3017};
static const unsigned long cp_single_3994[] = {0x25b9};
static const unsigned long cp_single_3995[] = {0x25b7};
static const unsigned long cp_single_3996[] = {0x25ab};
static const unsigned long cp_single_3997[] = {0x263a};
static const unsigned long cp_single_3998[] = {0x25a1};
static const unsigned long cp_single_3999[] = {0x2606};
static const unsigned long cp_single_4000[] = {0x260f};
static const unsigned long cp_single_4001[] = {0x3018};
static const unsigned long cp_single_4002[] = {0x3019};
static const unsigned long cp_single_4003[] = {0x25b5};
static const unsigned long cp_single_4004[] = {0x25b3};
static const unsigned long cp_single_4005[] = {0x3090};
static const unsigned long cp_single_4006[] = {0x30f0};
static const unsigned long cp_single_4007[] = {0x315f};
static const unsigned long cp_single_4008[] = {0xff57};
static const unsigned long cp_single_4009[] = {0x3092};
static const unsigned long cp_single_4010[] = {0x30f2};
static const unsigned long cp_single_4011[] = {0xff66};
static const unsigned long cp_single_4012[] = {0x20a9};
static const unsigned long cp_single_4013[] = {0xffe6};
static const unsigned long cp_single_4014[] = {0x0e27};
static const unsigned long cp_single_4015[] = {0x24b2};
static const unsigned long cp_single_4016[] = {0x1e98};
static const unsigned long cp_single_4017[] = {0x02b7};
static const unsigned long cp_single_4018[] = {0x028d};
static const unsigned long cp_single_4019[] = {0x01bf};
static const unsigned long cp_single_4020[] = {0x0078};
static const unsigned long cp_single_4021[] = {0x033d};
static const unsigned long cp_single_4022[] = {0x3112};
static const unsigned long cp_single_4023[] = {0x24e7};
static const unsigned long cp_single_4024[] = {0x1e8d};
static const unsigned long cp_single_4025[] = {0x1e8b};
static const unsigned long cp_single_4026[] = {0x056d};
static const unsigned long cp_single_4027[] = {0x03be};
static const unsigned long cp_single_4028[] = {0xff58};
static const unsigned long cp_single_4029[] = {0x24b3};
static const unsigned long cp_single_4030[] = {0x02e3};
static const unsigned long cp_single_4031[] = {0x0079};
static const unsigned long cp_single_4032[] = {0x334e};
static const unsigned long cp_single_4033[] = {0x09af};
static const unsigned long cp_single_4034[] = {0x00fd};
static const unsigned long cp_single_4035[] = {0x092f};
static const unsigned long cp_single_4036[] = {0x3152};
static const unsigned long cp_single_4037[] = {0x0aaf};
static const unsigned long cp_single_4038[] = {0x0a2f};
static const unsigned long cp_single_4039[] = {0x3084};
static const unsigned long cp_single_4040[] = {0x30e4};
static const unsigned long cp_single_4041[] = {0xff94};
static const unsigned long cp_single_4042[] = {0x3151};
static const unsigned long cp_single_4043[] = {0x0e4e};
static const unsigned long cp_single_4044[] = {0x3083};
static const unsigned long cp_single_4045[] = {0x30e3};
static const unsigned long cp_single_4046[] = {0xff6c};
static const unsigned long cp_single_4047[] = {0x0463};
static const unsigned long cp_single_4048[] = {0x24e8};
static const unsigned long cp_single_4049[] = {0x0177};
static const unsigned long cp_single_4050[] = {0x00ff};
static const unsigned long cp_single_4051[] = {0x1e8f};
static const unsigned long cp_single_4052[] = {0x1ef5};
static const unsigned long cp_single_4053[] = {0x064a};
static const unsigned long cp_single_4054[] = {0x06d2};
static const unsigned long cp_single_4055[] = {0xfbaf};
static const unsigned long cp_single_4056[] = {0xfef2};
static const unsigned long cp_single_4057[] = {0x0626};
static const unsigned long cp_single_4058[] = {0xfe8a};
static const unsigned long cp_single_4059[] = {0xfe8b};
static const unsigned long cp_single_4060[] = {0xfe8c};
static const unsigned long cp_single_4061[] = {0xfef3};
static const unsigned long cp_single_4062[] = {0xfef4};
static const unsigned long cp_single_4063[] = {0xfcdd};
static const unsigned long cp_single_4064[] = {0xfc58};
static const unsigned long cp_single_4065[] = {0xfc94};
static const unsigned long cp_single_4066[] = {0x06d1};
static const unsigned long cp_single_4067[] = {0x3156};
static const unsigned long cp_single_4068[] = {0x00a5};
static const unsigned long cp_single_4069[] = {0xffe5};
static const unsigned long cp_single_4070[] = {0x3155};
static const unsigned long cp_single_4071[] = {0x3186};
static const unsigned long cp_single_4072[] = {0x05aa};
static const unsigned long cp_single_4073[] = {0x05aa};
static const unsigned long cp_single_4074[] = {0x044b};
static const unsigned long cp_single_4075[] = {0x04f9};
static const unsigned long cp_single_4076[] = {0x3181};
static const unsigned long cp_single_4077[] = {0x3183};
static const unsigned long cp_single_4078[] = {0x3182};
static const unsigned long cp_single_4079[] = {0x059a};
static const unsigned long cp_single_4080[] = {0x1ef3};
static const unsigned long cp_single_4081[] = {0x01b4};
static const unsigned long cp_single_4082[] = {0x1ef7};
static const unsigned long cp_single_4083[] = {0x0575};
static const unsigned long cp_single_4084[] = {0x0457};
static const unsigned long cp_single_4085[] = {0x3162};
static const unsigned long cp_single_4086[] = {0x262f};
static const unsigned long cp_single_4087[] = {0x0582};
static const unsigned long cp_single_4088[] = {0xff59};
static const unsigned long cp_single_4089[] = {0x05d9};
static const unsigned long cp_single_4090[] = {0xfb39};
static const unsigned long cp_single_4091[] = {0xfb39};
static const unsigned long cp_single_4092[] = {0x05d9};
static const unsigned long cp_single_4093[] = {0x05f2};
static const unsigned long cp_single_4094[] = {0xfb1f};
static const unsigned long cp_single_4095[] = {0x3088};
static const unsigned long cp_single_4096[] = {0x3189};
static const unsigned long cp_single_4097[] = {0x30e8};
static const unsigned long cp_single_4098[] = {0xff96};
static const unsigned long cp_single_4099[] = {0x315b};
static const unsigned long cp_single_4100[] = {0x3087};
static const unsigned long cp_single_4101[] = {0x30e7};
static const unsigned long cp_single_4102[] = {0xff6e};
static const unsigned long cp_single_4103[] = {0x03f3};
static const unsigned long cp_single_4104[] = {0x3188};
static const unsigned long cp_single_4105[] = {0x3187};
static const unsigned long cp_single_4106[] = {0x0e22};
static const unsigned long cp_single_4107[] = {0x0e0d};
static const unsigned long cp_single_4108[] = {0x24b4};
static const unsigned long cp_single_4109[] = {0x037a};
static const unsigned long cp_single_4110[] = {0x0345};
static const unsigned long cp_single_4111[] = {0x01a6};
static const unsigned long cp_single_4112[] = {0x1e99};
static const unsigned long cp_single_4113[] = {0x02b8};
static const unsigned long cp_single_4114[] = {0x1ef9};
static const unsigned long cp_single_4115[] = {0x028e};
static const unsigned long cp_single_4116[] = {0x3086};
static const unsigned long cp_single_4117[] = {0x318c};
static const unsigned long cp_single_4118[] = {0x30e6};
static const unsigned long cp_single_4119[] = {0xff95};
static const unsigned long cp_single_4120[] = {0x3160};
static const unsigned long cp_single_4121[] = {0x046b};
static const unsigned long cp_single_4122[] = {0x046d};
static const unsigned long cp_single_4123[] = {0x0467};
static const unsigned long cp_single_4124[] = {0x0469};
static const unsigned long cp_single_4125[] = {0x3085};
static const unsigned long cp_single_4126[] = {0x30e5};
static const unsigned long cp_single_4127[] = {0xff6d};
static const unsigned long cp_single_4128[] = {0x318b};
static const unsigned long cp_single_4129[] = {0x318a};
static const unsigned long cp_single_4130[] = {0x09df};
static const unsigned long cp_single_4131[] = {0x095f};
static const unsigned long cp_single_4132[] = {0x007a};
static const unsigned long cp_single_4133[] = {0x0566};
static const unsigned long cp_single_4134[] = {0x017a};
static const unsigned long cp_single_4135[] = {0x095b};
static const unsigned long cp_single_4136[] = {0x0a5b};
static const unsigned long cp_single_4137[] = {0x0638};
static const unsigned long cp_single_4138[] = {0xfec6};
static const unsigned long cp_single_4139[] = {0xfec7};
static const unsigned long cp_single_4140[] = {0x3056};
static const unsigned long cp_single_4141[] = {0xfec8};
static const unsigned long cp_single_4142[] = {0x0632};
static const unsigned long cp_single_4143[] = {0xfeb0};
static const unsigned long cp_single_4144[] = {0x30b6};
static const unsigned long cp_single_4145[] = {0x0595};
static const unsigned long cp_single_4146[] = {0x0594};
static const unsigned long cp_single_4147[] = {0x0598};
static const unsigned long cp_single_4148[] = {0x05d6};
static const unsigned long cp_single_4149[] = {0xfb36};
static const unsigned long cp_single_4150[] = {0xfb36};
static const unsigned long cp_single_4151[] = {0x05d6};
static const unsigned long cp_single_4152[] = {0x3117};
static const unsigned long cp_single_4153[] = {0x017e};
static const unsigned long cp_single_4154[] = {0x24e9};
static const unsigned long cp_single_4155[] = {0x1e91};
static const unsigned long cp_single_4156[] = {0x0291};
static const unsigned long cp_single_4157[] = {0x017c};
static const unsigned long cp_single_4158[] = {0x017c};
static const unsigned long cp_single_4159[] = {0x1e93};
static const unsigned long cp_single_4160[] = {0x0437};
static const unsigned long cp_single_4161[] = {0x0499};
static const unsigned long cp_single_4162[] = {0x04df};
static const unsigned long cp_single_4163[] = {0x305c};
static const unsigned long cp_single_4164[] = {0x30bc};
static const unsigned long cp_single_4165[] = {0x0030};
static const unsigned long cp_single_4166[] = {0x0660};
static const unsigned long cp_single_4167[] = {0x09e6};
static const unsigned long cp_single_4168[] = {0x0966};
static const unsigned long cp_single_4169[] = {0x0ae6};
static const unsigned long cp_single_4170[] = {0x0a66};
static const unsigned long cp_single_4171[] = {0x0660};
static const unsigned long cp_single_4172[] = {0x2080};
static const unsigned long cp_single_4173[] = {0xff10};
static const unsigned long cp_single_4174[] = {0xf730};
static const unsigned long cp_single_4175[] = {0x06f0};
static const unsigned long cp_single_4176[] = {0x2070};
static const unsigned long cp_single_4177[] = {0x0e50};
static const unsigned long cp_single_4178[] = {0xfeff};
static const unsigned long cp_single_4179[] = {0x200c};
static const unsigned long cp_single_4180[] = {0x200b};
static const unsigned long cp_single_4181[] = {0x03b6};
static const unsigned long cp_single_4182[] = {0x3113};
static const unsigned long cp_single_4183[] = {0x056a};
static const unsigned long cp_single_4184[] = {0x04c2};
static const unsigned long cp_single_4185[] = {0x0436};
static const unsigned long cp_single_4186[] = {0x0497};
static const unsigned long cp_single_4187[] = {0x04dd};
static const unsigned long cp_single_4188[] = {0x3058};
static const unsigned long cp_single_4189[] = {0x30b8};
static const unsigned long cp_single_4190[] = {0x05ae};
static const unsigned long cp_single_4191[] = {0x1e95};
static const unsigned long cp_single_4192[] = {0xff5a};
static const unsigned long cp_single_4193[] = {0x305e};
static const unsigned long cp_single_4194[] = {0x30be};
static const unsigned long cp_single_4195[] = {0x24b5};
static const unsigned long cp_single_4196[] = {0x0290};
static const unsigned long cp_single_4197[] = {0x01b6};
static const unsigned long cp_single_4198[] = {0x305a};
static const unsigned long cp_single_4199[] = {0x30ba};

const GlyphListEntry AdobeGlyphListData[] = {
    {"A", cp_single_0, 1},
    {"AE", cp_single_1, 1},
    {"AEacute", cp_single_2, 1},
    {"AEmacron", cp_single_3, 1},
    {"AEsmall", cp_single_4, 1},
    {"Aacute", cp_single_5, 1},
    {"Aacutesmall", cp_single_6, 1},
    {"Abreve", cp_single_7, 1},
    {"Abreveacute", cp_single_8, 1},
    {"Abrevecyrillic", cp_single_9, 1},
    {"Abrevedotbelow", cp_single_10, 1},
    {"Abrevegrave", cp_single_11, 1},
    {"Abrevehookabove", cp_single_12, 1},
    {"Abrevetilde", cp_single_13, 1},
    {"Acaron", cp_single_14, 1},
    {"Acircle", cp_single_15, 1},
    {"Acircumflex", cp_single_16, 1},
    {"Acircumflexacute", cp_single_17, 1},
    {"Acircumflexdotbelow", cp_single_18, 1},
    {"Acircumflexgrave", cp_single_19, 1},
    {"Acircumflexhookabove", cp_single_20, 1},
    {"Acircumflexsmall", cp_single_21, 1},
    {"Acircumflextilde", cp_single_22, 1},
    {"Acute", cp_single_23, 1},
    {"Acutesmall", cp_single_24, 1},
    {"Acyrillic", cp_single_25, 1},
    {"Adblgrave", cp_single_26, 1},
    {"Adieresis", cp_single_27, 1},
    {"Adieresiscyrillic", cp_single_28, 1},
    {"Adieresismacron", cp_single_29, 1},
    {"Adieresissmall", cp_single_30, 1},
    {"Adotbelow", cp_single_31, 1},
    {"Adotmacron", cp_single_32, 1},
    {"Agrave", cp_single_33, 1},
    {"Agravesmall", cp_single_34, 1},
    {"Ahookabove", cp_single_35, 1},
    {"Aiecyrillic", cp_single_36, 1},
    {"Ainvertedbreve", cp_single_37, 1},
    {"Alpha", cp_single_38, 1},
    {"Alphatonos", cp_single_39, 1},
    {"Amacron", cp_single_40, 1},
    {"Amonospace", cp_single_41, 1},
    {"Aogonek", cp_single_42, 1},
    {"Aring", cp_single_43, 1},
    {"Aringacute", cp_single_44, 1},
    {"Aringbelow", cp_single_45, 1},
    {"Aringsmall", cp_single_46, 1},
    {"Asmall", cp_single_47, 1},
    {"Atilde", cp_single_48, 1},
    {"Atildesmall", cp_single_49, 1},
    {"Aybarmenian", cp_single_50, 1},
    {"B", cp_single_51, 1},
    {"Bcircle", cp_single_52, 1},
    {"Bdotaccent", cp_single_53, 1},
    {"Bdotbelow", cp_single_54, 1},
    {"Becyrillic", cp_single_55, 1},
    {"Benarmenian", cp_single_56, 1},
    {"Beta", cp_single_57, 1},
    {"Bhook", cp_single_58, 1},
    {"Blinebelow", cp_single_59, 1},
    {"Bmonospace", cp_single_60, 1},
    {"Brevesmall", cp_single_61, 1},
    {"Bsmall", cp_single_62, 1},
    {"Btopbar", cp_single_63, 1},
    {"C", cp_single_64, 1},
    {"Caarmenian", cp_single_65, 1},
    {"Cacute", cp_single_66, 1},
    {"Caron", cp_single_67, 1},
    {"Caronsmall", cp_single_68, 1},
    {"Ccaron", cp_single_69, 1},
    {"Ccedilla", cp_single_70, 1},
    {"Ccedillaacute", cp_single_71, 1},
    {"Ccedillasmall", cp_single_72, 1},
    {"Ccircle", cp_single_73, 1},
    {"Ccircumflex", cp_single_74, 1},
    {"Cdot", cp_single_75, 1},
    {"Cdotaccent", cp_single_76, 1},
    {"Cedillasmall", cp_single_77, 1},
    {"Chaarmenian", cp_single_78, 1},
    {"Cheabkhasiancyrillic", cp_single_79, 1},
    {"Checyrillic", cp_single_80, 1},
    {"Chedescenderabkhasiancyrillic", cp_single_81, 1},
    {"Chedescendercyrillic", cp_single_82, 1},
    {"Chedieresiscyrillic", cp_single_83, 1},
    {"Cheharmenian", cp_single_84, 1},
    {"Chekhakassiancyrillic", cp_single_85, 1},
    {"Cheverticalstrokecyrillic", cp_single_86, 1},
    {"Chi", cp_single_87, 1},
    {"Chook", cp_single_88, 1},
    {"Circumflexsmall", cp_single_89, 1},
    {"Cmonospace", cp_single_90, 1},
    {"Coarmenian", cp_single_91, 1},
    {"Csmall", cp_single_92, 1},
    {"D", cp_single_93, 1},
    {"DZ", cp_single_94, 1},
    {"DZcaron", cp_single_95, 1},
    {"Daarmenian", cp_single_96, 1},
    {"Dafrican", cp_single_97, 1},
    {"Dcaron", cp_single_98, 1},
    {"Dcedilla", cp_single_99, 1},
    {"Dcircle", cp_single_100, 1},
    {"Dcircumflexbelow", cp_single_101, 1},
    {"Dcroat", cp_single_102, 1},
    {"Ddotaccent", cp_single_103, 1},
    {"Ddotbelow", cp_single_104, 1},
    {"Decyrillic", cp_single_105, 1},
    {"Deicoptic", cp_single_106, 1},
    {"Delta", cp_single_107, 1},
    {"Deltagreek", cp_single_108, 1},
    {"Dhook", cp_single_109, 1},
    {"Dieresis", cp_single_110, 1},
    {"DieresisAcute", cp_single_111, 1},
    {"DieresisGrave", cp_single_112, 1},
    {"Dieresissmall", cp_single_113, 1},
    {"Digammagreek", cp_single_114, 1},
    {"Djecyrillic", cp_single_115, 1},
    {"Dlinebelow", cp_single_116, 1},
    {"Dmonospace", cp_single_117, 1},
    {"Dotaccentsmall", cp_single_118, 1},
    {"Dslash", cp_single_119, 1},
    {"Dsmall", cp_single_120, 1},
    {"Dtopbar", cp_single_121, 1},
    {"Dz", cp_single_122, 1},
    {"Dzcaron", cp_single_123, 1},
    {"Dzeabkhasiancyrillic", cp_single_124, 1},
    {"Dzecyrillic", cp_single_125, 1},
    {"Dzhecyrillic", cp_single_126, 1},
    {"E", cp_single_127, 1},
    {"Eacute", cp_single_128, 1},
    {"Eacutesmall", cp_single_129, 1},
    {"Ebreve", cp_single_130, 1},
    {"Ecaron", cp_single_131, 1},
    {"Ecedillabreve", cp_single_132, 1},
    {"Echarmenian", cp_single_133, 1},
    {"Ecircle", cp_single_134, 1},
    {"Ecircumflex", cp_single_135, 1},
    {"Ecircumflexacute", cp_single_136, 1},
    {"Ecircumflexbelow", cp_single_137, 1},
    {"Ecircumflexdotbelow", cp_single_138, 1},
    {"Ecircumflexgrave", cp_single_139, 1},
    {"Ecircumflexhookabove", cp_single_140, 1},
    {"Ecircumflexsmall", cp_single_141, 1},
    {"Ecircumflextilde", cp_single_142, 1},
    {"Ecyrillic", cp_single_143, 1},
    {"Edblgrave", cp_single_144, 1},
    {"Edieresis", cp_single_145, 1},
    {"Edieresissmall", cp_single_146, 1},
    {"Edot", cp_single_147, 1},
    {"Edotaccent", cp_single_148, 1},
    {"Edotbelow", cp_single_149, 1},
    {"Efcyrillic", cp_single_150, 1},
    {"Egrave", cp_single_151, 1},
    {"Egravesmall", cp_single_152, 1},
    {"Eharmenian", cp_single_153, 1},
    {"Ehookabove", cp_single_154, 1},
    {"Eightroman", cp_single_155, 1},
    {"Einvertedbreve", cp_single_156, 1},
    {"Eiotifiedcyrillic", cp_single_157, 1},
    {"Elcyrillic", cp_single_158, 1},
    {"Elevenroman", cp_single_159, 1},
    {"Emacron", cp_single_160, 1},
    {"Emacronacute", cp_single_161, 1},
    {"Emacrongrave", cp_single_162, 1},
    {"Emcyrillic", cp_single_163, 1},
    {"Emonospace", cp_single_164, 1},
    {"Encyrillic", cp_single_165, 1},
    {"Endescendercyrillic", cp_single_166, 1},
    {"Eng", cp_single_167, 1},
    {"Enghecyrillic", cp_single_168, 1},
    {"Enhookcyrillic", cp_single_169, 1},
    {"Eogonek", cp_single_170, 1},
    {"Eopen", cp_single_171, 1},
    {"Epsilon", cp_single_172, 1},
    {"Epsilontonos", cp_single_173, 1},
    {"Ercyrillic", cp_single_174, 1},
    {"Ereversed", cp_single_175, 1},
    {"Ereversedcyrillic", cp_single_176, 1},
    {"Escyrillic", cp_single_177, 1},
    {"Esdescendercyrillic", cp_single_178, 1},
    {"Esh", cp_single_179, 1},
    {"Esmall", cp_single_180, 1},
    {"Eta", cp_single_181, 1},
    {"Etarmenian", cp_single_182, 1},
    {"Etatonos", cp_single_183, 1},
    {"Eth", cp_single_184, 1},
    {"Ethsmall", cp_single_185, 1},
    {"Etilde", cp_single_186, 1},
    {"Etildebelow", cp_single_187, 1},
    {"Euro", cp_single_188, 1},
    {"Ezh", cp_single_189, 1},
    {"Ezhcaron", cp_single_190, 1},
    {"Ezhreversed", cp_single_191, 1},
    {"F", cp_single_192, 1},
    {"Fcircle", cp_single_193, 1},
    {"Fdotaccent", cp_single_194, 1},
    {"Feharmenian", cp_single_195, 1},
    {"Feicoptic", cp_single_196, 1},
    {"Fhook", cp_single_197, 1},
    {"Fitacyrillic", cp_single_198, 1},
    {"Fiveroman", cp_single_199, 1},
    {"Fmonospace", cp_single_200, 1},
    {"Fourroman", cp_single_201, 1},
    {"Fsmall", cp_single_202, 1},
    {"G", cp_single_203, 1},
    {"GBsquare", cp_single_204, 1},
    {"Gacute", cp_single_205, 1},
    {"Gamma", cp_single_206, 1},
    {"Gammaafrican", cp_single_207, 1},
    {"Gangiacoptic", cp_single_208, 1},
    {"Gbreve", cp_single_209, 1},
    {"Gcaron", cp_single_210, 1},
    {"Gcedilla", cp_single_211, 1},
    {"Gcircle", cp_single_212, 1},
    {"Gcircumflex", cp_single_213, 1},
    {"Gcommaaccent", cp_single_214, 1},
    {"Gdot", cp_single_215, 1},
    {"Gdotaccent", cp_single_216, 1},
    {"Gecyrillic", cp_single_217, 1},
    {"Ghadarmenian", cp_single_218, 1},
    {"Ghemiddlehookcyrillic", cp_single_219, 1},
    {"Ghestrokecyrillic", cp_single_220, 1},
    {"Gheupturncyrillic", cp_single_221, 1},
    {"Ghook", cp_single_222, 1},
    {"Gimarmenian", cp_single_223, 1},
    {"Gjecyrillic", cp_single_224, 1},
    {"Gmacron", cp_single_225, 1},
    {"Gmonospace", cp_single_226, 1},
    {"Grave", cp_single_227, 1},
    {"Gravesmall", cp_single_228, 1},
    {"Gsmall", cp_single_229, 1},
    {"Gsmallhook", cp_single_230, 1},
    {"Gstroke", cp_single_231, 1},
    {"H", cp_single_232, 1},
    {"H18533", cp_single_233, 1},
    {"H18543", cp_single_234, 1},
    {"H18551", cp_single_235, 1},
    {"H22073", cp_single_236, 1},
    {"HPsquare", cp_single_237, 1},
    {"Haabkhasiancyrillic", cp_single_238, 1},
    {"Hadescendercyrillic", cp_single_239, 1},
    {"Hardsigncyrillic", cp_single_240, 1},
    {"Hbar", cp_single_241, 1},
    {"Hbrevebelow", cp_single_242, 1},
    {"Hcedilla", cp_single_243, 1},
    {"Hcircle", cp_single_244, 1},
    {"Hcircumflex", cp_single_245, 1},
    {"Hdieresis", cp_single_246, 1},
    {"Hdotaccent", cp_single_247, 1},
    {"Hdotbelow", cp_single_248, 1},
    {"Hmonospace", cp_single_249, 1},
    {"Hoarmenian", cp_single_250, 1},
    {"Horicoptic", cp_single_251, 1},
    {"Hsmall", cp_single_252, 1},
    {"Hungarumlaut", cp_single_253, 1},
    {"Hungarumlautsmall", cp_single_254, 1},
    {"Hzsquare", cp_single_255, 1},
    {"I", cp_single_256, 1},
    {"IAcyrillic", cp_single_257, 1},
    {"IJ", cp_single_258, 1},
    {"IUcyrillic", cp_single_259, 1},
    {"Iacute", cp_single_260, 1},
    {"Iacutesmall", cp_single_261, 1},
    {"Ibreve", cp_single_262, 1},
    {"Icaron", cp_single_263, 1},
    {"Icircle", cp_single_264, 1},
    {"Icircumflex", cp_single_265, 1},
    {"Icircumflexsmall", cp_single_266, 1},
    {"Icyrillic", cp_single_267, 1},
    {"Idblgrave", cp_single_268, 1},
    {"Idieresis", cp_single_269, 1},
    {"Idieresisacute", cp_single_270, 1},
    {"Idieresiscyrillic", cp_single_271, 1},
    {"Idieresissmall", cp_single_272, 1},
    {"Idot", cp_single_273, 1},
    {"Idotaccent", cp_single_274, 1},
    {"Idotbelow", cp_single_275, 1},
    {"Iebrevecyrillic", cp_single_276, 1},
    {"Iecyrillic", cp_single_277, 1},
    {"Ifraktur", cp_single_278, 1},
    {"Igrave", cp_single_279, 1},
    {"Igravesmall", cp_single_280, 1},
    {"Ihookabove", cp_single_281, 1},
    {"Iicyrillic", cp_single_282, 1},
    {"Iinvertedbreve", cp_single_283, 1},
    {"Iishortcyrillic", cp_single_284, 1},
    {"Imacron", cp_single_285, 1},
    {"Imacroncyrillic", cp_single_286, 1},
    {"Imonospace", cp_single_287, 1},
    {"Iniarmenian", cp_single_288, 1},
    {"Iocyrillic", cp_single_289, 1},
    {"Iogonek", cp_single_290, 1},
    {"Iota", cp_single_291, 1},
    {"Iotaafrican", cp_single_292, 1},
    {"Iotadieresis", cp_single_293, 1},
    {"Iotatonos", cp_single_294, 1},
    {"Ismall", cp_single_295, 1},
    {"Istroke", cp_single_296, 1},
    {"Itilde", cp_single_297, 1},
    {"Itildebelow", cp_single_298, 1},
    {"Izhitsacyrillic", cp_single_299, 1},
    {"Izhitsadblgravecyrillic", cp_single_300, 1},
    {"J", cp_single_301, 1},
    {"Jaarmenian", cp_single_302, 1},
    {"Jcircle", cp_single_303, 1},
    {"Jcircumflex", cp_single_304, 1},
    {"Jecyrillic", cp_single_305, 1},
    {"Jheharmenian", cp_single_306, 1},
    {"Jmonospace", cp_single_307, 1},
    {"Jsmall", cp_single_308, 1},
    {"K", cp_single_309, 1},
    {"KBsquare", cp_single_310, 1},
    {"KKsquare", cp_single_311, 1},
    {"Kabashkircyrillic", cp_single_312, 1},
    {"Kacute", cp_single_313, 1},
    {"Kacyrillic", cp_single_314, 1},
    {"Kadescendercyrillic", cp_single_315, 1},
    {"Kahookcyrillic", cp_single_316, 1},
    {"Kappa", cp_single_317, 1},
    {"Kastrokecyrillic", cp_single_318, 1},
    {"Kaverticalstrokecyrillic", cp_single_319, 1},
    {"Kcaron", cp_single_320, 1},
    {"Kcedilla", cp_single_321, 1},
    {"Kcircle", cp_single_322, 1},
    {"Kcommaaccent", cp_single_323, 1},
    {"Kdotbelow", cp_single_324, 1},
    {"Keharmenian", cp_single_325, 1},
    {"Kenarmenian", cp_single_326, 1},
    {"Khacyrillic", cp_single_327, 1},
    {"Kheicoptic", cp_single_328, 1},
    {"Khook", cp_single_329, 1},
    {"Kjecyrillic", cp_single_330, 1},
    {"Klinebelow", cp_single_331, 1},
    {"Kmonospace", cp_single_332, 1},
    {"Koppacyrillic", cp_single_333, 1},
    {"Koppagreek", cp_single_334, 1},
    {"Ksicyrillic", cp_single_335, 1},
    {"Ksmall", cp_single_336, 1},
    {"L", cp_single_337, 1},
    {"LJ", cp_single_338, 1},
    {"LL", cp_single_339, 1},
    {"Lacute", cp_single_340, 1},
    {"Lambda", cp_single_341, 1},
    {"Lcaron", cp_single_342, 1},
    {"Lcedilla", cp_single_343, 1},
    {"Lcircle", cp_single_344, 1},
    {"Lcircumflexbelow", cp_single_345, 1},
    {"Lcommaaccent", cp_single_346, 1},
    {"Ldot", cp_single_347, 1},
    {"Ldotaccent", cp_single_348, 1},
    {"Ldotbelow", cp_single_349, 1},
    {"Ldotbelowmacron", cp_single_350, 1},
    {"Liwnarmenian", cp_single_351, 1},
    {"Lj", cp_single_352, 1},
    {"Ljecyrillic", cp_single_353, 1},
    {"Llinebelow", cp_single_354, 1},
    {"Lmonospace", cp_single_355, 1},
    {"Lslash", cp_single_356, 1},
    {"Lslashsmall", cp_single_357, 1},
    {"Lsmall", cp_single_358, 1},
    {"M", cp_single_359, 1},
    {"MBsquare", cp_single_360, 1},
    {"Macron", cp_single_361, 1},
    {"Macronsmall", cp_single_362, 1},
    {"Macute", cp_single_363, 1},
    {"Mcircle", cp_single_364, 1},
    {"Mdotaccent", cp_single_365, 1},
    {"Mdotbelow", cp_single_366, 1},
    {"Menarmenian", cp_single_367, 1},
    {"Mmonospace", cp_single_368, 1},
    {"Msmall", cp_single_369, 1},
    {"Mturned", cp_single_370, 1},
    {"Mu", cp_single_371, 1},
    {"N", cp_single_372, 1},
    {"NJ", cp_single_373, 1},
    {"Nacute", cp_single_374, 1},
    {"Ncaron", cp_single_375, 1},
    {"Ncedilla", cp_single_376, 1},
    {"Ncircle", cp_single_377, 1},
    {"Ncircumflexbelow", cp_single_378, 1},
    {"Ncommaaccent", cp_single_379, 1},
    {"Ndotaccent", cp_single_380, 1},
    {"Ndotbelow", cp_single_381, 1},
    {"Nhookleft", cp_single_382, 1},
    {"Nineroman", cp_single_383, 1},
    {"Nj", cp_single_384, 1},
    {"Njecyrillic", cp_single_385, 1},
    {"Nlinebelow", cp_single_386, 1},
    {"Nmonospace", cp_single_387, 1},
    {"Nowarmenian", cp_single_388, 1},
    {"Nsmall", cp_single_389, 1},
    {"Ntilde", cp_single_390, 1},
    {"Ntildesmall", cp_single_391, 1},
    {"Nu", cp_single_392, 1},
    {"O", cp_single_393, 1},
    {"OE", cp_single_394, 1},
    {"OEsmall", cp_single_395, 1},
    {"Oacute", cp_single_396, 1},
    {"Oacutesmall", cp_single_397, 1},
    {"Obarredcyrillic", cp_single_398, 1},
    {"Obarreddieresiscyrillic", cp_single_399, 1},
    {"Obreve", cp_single_400, 1},
    {"Ocaron", cp_single_401, 1},
    {"Ocenteredtilde", cp_single_402, 1},
    {"Ocircle", cp_single_403, 1},
    {"Ocircumflex", cp_single_404, 1},
    {"Ocircumflexacute", cp_single_405, 1},
    {"Ocircumflexdotbelow", cp_single_406, 1},
    {"Ocircumflexgrave", cp_single_407, 1},
    {"Ocircumflexhookabove", cp_single_408, 1},
    {"Ocircumflexsmall", cp_single_409, 1},
    {"Ocircumflextilde", cp_single_410, 1},
    {"Ocyrillic", cp_single_411, 1},
    {"Odblacute", cp_single_412, 1},
    {"Odblgrave", cp_single_413, 1},
    {"Odieresis", cp_single_414, 1},
    {"Odieresiscyrillic", cp_single_415, 1},
    {"Odieresissmall", cp_single_416, 1},
    {"Odotbelow", cp_single_417, 1},
    {"Ogoneksmall", cp_single_418, 1},
    {"Ograve", cp_single_419, 1},
    {"Ogravesmall", cp_single_420, 1},
    {"Oharmenian", cp_single_421, 1},
    {"Ohm", cp_single_422, 1},
    {"Ohookabove", cp_single_423, 1},
    {"Ohorn", cp_single_424, 1},
    {"Ohornacute", cp_single_425, 1},
    {"Ohorndotbelow", cp_single_426, 1},
    {"Ohorngrave", cp_single_427, 1},
    {"Ohornhookabove", cp_single_428, 1},
    {"Ohorntilde", cp_single_429, 1},
    {"Ohungarumlaut", cp_single_430, 1},
    {"Oi", cp_single_431, 1},
    {"Oinvertedbreve", cp_single_432, 1},
    {"Omacron", cp_single_433, 1},
    {"Omacronacute", cp_single_434, 1},
    {"Omacrongrave", cp_single_435, 1},
    {"Omega", cp_single_436, 1},
    {"Omegacyrillic", cp_single_437, 1},
    {"Omegagreek", cp_single_438, 1},
    {"Omegaroundcyrillic", cp_single_439, 1},
    {"Omegatitlocyrillic", cp_single_440, 1},
    {"Omegatonos", cp_single_441, 1},
    {"Omicron", cp_single_442, 1},
    {"Omicrontonos", cp_single_443, 1},
    {"Omonospace", cp_single_444, 1},
    {"Oneroman", cp_single_445, 1},
    {"Oogonek", cp_single_446, 1},
    {"Oogonekmacron", cp_single_447, 1},
    {"Oopen", cp_single_448, 1},
    {"Oslash", cp_single_449, 1},
    {"Oslashacute", cp_single_450, 1},
    {"Oslashsmall", cp_single_451, 1},
    {"Osmall", cp_single_452, 1},
    {"Ostrokeacute", cp_single_453, 1},
    {"Otcyrillic", cp_single_454, 1},
    {"Otilde", cp_single_455, 1},
    {"Otildeacute", cp_single_456, 1},
    {"Otildedieresis", cp_single_457, 1},
    {"Otildesmall", cp_single_458, 1},
    {"P", cp_single_459, 1},
    {"Pacute", cp_single_460, 1},
    {"Pcircle", cp_single_461, 1},
    {"Pdotaccent", cp_single_462, 1},
    {"Pecyrillic", cp_single_463, 1},
    {"Peharmenian", cp_single_464, 1},
    {"Pemiddlehookcyrillic", cp_single_465, 1},
    {"Phi", cp_single_466, 1},
    {"Phook", cp_single_467, 1},
    {"Pi", cp_single_468, 1},
    {"Piwrarmenian", cp_single_469, 1},
    {"Pmonospace", cp_single_470, 1},
    {"Psi", cp_single_471, 1},
    {"Psicyrillic", cp_single_472, 1},
    {"Psmall", cp_single_473, 1},
    {"Q", cp_single_474, 1},
    {"Qcircle", cp_single_475, 1},
    {"Qmonospace", cp_single_476, 1},
    {"Qsmall", cp_single_477, 1},
    {"R", cp_single_478, 1},
    {"Raarmenian", cp_single_479, 1},
    {"Racute", cp_single_480, 1},
    {"Rcaron", cp_single_481, 1},
    {"Rcedilla", cp_single_482, 1},
    {"Rcircle", cp_single_483, 1},
    {"Rcommaaccent", cp_single_484, 1},
    {"Rdblgrave", cp_single_485, 1},
    {"Rdotaccent", cp_single_486, 1},
    {"Rdotbelow", cp_single_487, 1},
    {"Rdotbelowmacron", cp_single_488, 1},
    {"Reharmenian", cp_single_489, 1},
    {"Rfraktur", cp_single_490, 1},
    {"Rho", cp_single_491, 1},
    {"Ringsmall", cp_single_492, 1},
    {"Rinvertedbreve", cp_single_493, 1},
    {"Rlinebelow", cp_single_494, 1},
    {"Rmonospace", cp_single_495, 1},
    {"Rsmall", cp_single_496, 1},
    {"Rsmallinverted", cp_single_497, 1},
    {"Rsmallinvertedsuperior", cp_single_498, 1},
    {"S", cp_single_499, 1},
    {"SF010000", cp_single_500, 1},
    {"SF020000", cp_single_501, 1},
    {"SF030000", cp_single_502, 1},
    {"SF040000", cp_single_503, 1},
    {"SF050000", cp_single_504, 1},
    {"SF060000", cp_single_505, 1},
    {"SF070000", cp_single_506, 1},
    {"SF080000", cp_single_507, 1},
    {"SF090000", cp_single_508, 1},
    {"SF100000", cp_single_509, 1},
    {"SF110000", cp_single_510, 1},
    {"SF190000", cp_single_511, 1},
    {"SF200000", cp_single_512, 1},
    {"SF210000", cp_single_513, 1},
    {"SF220000", cp_single_514, 1},
    {"SF230000", cp_single_515, 1},
    {"SF240000", cp_single_516, 1},
    {"SF250000", cp_single_517, 1},
    {"SF260000", cp_single_518, 1},
    {"SF270000", cp_single_519, 1},
    {"SF280000", cp_single_520, 1},
    {"SF360000", cp_single_521, 1},
    {"SF370000", cp_single_522, 1},
    {"SF380000", cp_single_523, 1},
    {"SF390000", cp_single_524, 1},
    {"SF400000", cp_single_525, 1},
    {"SF410000", cp_single_526, 1},
    {"SF420000", cp_single_527, 1},
    {"SF430000", cp_single_528, 1},
    {"SF440000", cp_single_529, 1},
    {"SF450000", cp_single_530, 1},
    {"SF460000", cp_single_531, 1},
    {"SF470000", cp_single_532, 1},
    {"SF480000", cp_single_533, 1},
    {"SF490000", cp_single_534, 1},
    {"SF500000", cp_single_535, 1},
    {"SF510000", cp_single_536, 1},
    {"SF520000", cp_single_537, 1},
    {"SF530000", cp_single_538, 1},
    {"SF540000", cp_single_539, 1},
    {"Sacute", cp_single_540, 1},
    {"Sacutedotaccent", cp_single_541, 1},
    {"Sampigreek", cp_single_542, 1},
    {"Scaron", cp_single_543, 1},
    {"Scarondotaccent", cp_single_544, 1},
    {"Scaronsmall", cp_single_545, 1},
    {"Scedilla", cp_single_546, 1},
    {"Schwa", cp_single_547, 1},
    {"Schwacyrillic", cp_single_548, 1},
    {"Schwadieresiscyrillic", cp_single_549, 1},
    {"Scircle", cp_single_550, 1},
    {"Scircumflex", cp_single_551, 1},
    {"Scommaaccent", cp_single_552, 1},
    {"Sdotaccent", cp_single_553, 1},
    {"Sdotbelow", cp_single_554, 1},
    {"Sdotbelowdotaccent", cp_single_555, 1},
    {"Seharmenian", cp_single_556, 1},
    {"Sevenroman", cp_single_557, 1},
    {"Shaarmenian", cp_single_558, 1},
    {"Shacyrillic", cp_single_559, 1},
    {"Shchacyrillic", cp_single_560, 1},
    {"Sheicoptic", cp_single_561, 1},
    {"Shhacyrillic", cp_single_562, 1},
    {"Shimacoptic", cp_single_563, 1},
    {"Sigma", cp_single_564, 1},
    {"Sixroman", cp_single_565, 1},
    {"Smonospace", cp_single_566, 1},
    {"Softsigncyrillic", cp_single_567, 1},
    {"Ssmall", cp_single_568, 1},
    {"Stigmagreek", cp_single_569, 1},
    {"T", cp_single_570, 1},
    {"Tau", cp_single_571, 1},
    {"Tbar", cp_single_572, 1},
    {"Tcaron", cp_single_573, 1},
    {"Tcedilla", cp_single_574, 1},
    {"Tcircle", cp_single_575, 1},
    {"Tcircumflexbelow", cp_single_576, 1},
    {"Tcommaaccent", cp_single_577, 1},
    {"Tdotaccent", cp_single_578, 1},
    {"Tdotbelow", cp_single_579, 1},
    {"Tecyrillic", cp_single_580, 1},
    {"Tedescendercyrillic", cp_single_581, 1},
    {"Tenroman", cp_single_582, 1},
    {"Tetsecyrillic", cp_single_583, 1},
    {"Theta", cp_single_584, 1},
    {"Thook", cp_single_585, 1},
    {"Thorn", cp_single_586, 1},
    {"Thornsmall", cp_single_587, 1},
    {"Threeroman", cp_single_588, 1},
    {"Tildesmall", cp_single_589, 1},
    {"Tiwnarmenian", cp_single_590, 1},
    {"Tlinebelow", cp_single_591, 1},
    {"Tmonospace", cp_single_592, 1},
    {"Toarmenian", cp_single_593, 1},
    {"Tonefive", cp_single_594, 1},
    {"Tonesix", cp_single_595, 1},
    {"Tonetwo", cp_single_596, 1},
    {"Tretroflexhook", cp_single_597, 1},
    {"Tsecyrillic", cp_single_598, 1},
    {"Tshecyrillic", cp_single_599, 1},
    {"Tsmall", cp_single_600, 1},
    {"Twelveroman", cp_single_601, 1},
    {"Tworoman", cp_single_602, 1},
    {"U", cp_single_603, 1},
    {"Uacute", cp_single_604, 1},
    {"Uacutesmall", cp_single_605, 1},
    {"Ubreve", cp_single_606, 1},
    {"Ucaron", cp_single_607, 1},
    {"Ucircle", cp_single_608, 1},
    {"Ucircumflex", cp_single_609, 1},
    {"Ucircumflexbelow", cp_single_610, 1},
    {"Ucircumflexsmall", cp_single_611, 1},
    {"Ucyrillic", cp_single_612, 1},
    {"Udblacute", cp_single_613, 1},
    {"Udblgrave", cp_single_614, 1},
    {"Udieresis", cp_single_615, 1},
    {"Udieresisacute", cp_single_616, 1},
    {"Udieresisbelow", cp_single_617, 1},
    {"Udieresiscaron", cp_single_618, 1},
    {"Udieresiscyrillic", cp_single_619, 1},
    {"Udieresisgrave", cp_single_620, 1},
    {"Udieresismacron", cp_single_621, 1},
    {"Udieresissmall", cp_single_622, 1},
    {"Udotbelow", cp_single_623, 1},
    {"Ugrave", cp_single_624, 1},
    {"Ugravesmall", cp_single_625, 1},
    {"Uhookabove", cp_single_626, 1},
    {"Uhorn", cp_single_627, 1},
    {"Uhornacute", cp_single_628, 1},
    {"Uhorndotbelow", cp_single_629, 1},
    {"Uhorngrave", cp_single_630, 1},
    {"Uhornhookabove", cp_single_631, 1},
    {"Uhorntilde", cp_single_632, 1},
    {"Uhungarumlaut", cp_single_633, 1},
    {"Uhungarumlautcyrillic", cp_single_634, 1},
    {"Uinvertedbreve", cp_single_635, 1},
    {"Ukcyrillic", cp_single_636, 1},
    {"Umacron", cp_single_637, 1},
    {"Umacroncyrillic", cp_single_638, 1},
    {"Umacrondieresis", cp_single_639, 1},
    {"Umonospace", cp_single_640, 1},
    {"Uogonek", cp_single_641, 1},
    {"Upsilon", cp_single_642, 1},
    {"Upsilon1", cp_single_643, 1},
    {"Upsilonacutehooksymbolgreek", cp_single_644, 1},
    {"Upsilonafrican", cp_single_645, 1},
    {"Upsilondieresis", cp_single_646, 1},
    {"Upsilondieresishooksymbolgreek", cp_single_647, 1},
    {"Upsilonhooksymbol", cp_single_648, 1},
    {"Upsilontonos", cp_single_649, 1},
    {"Uring", cp_single_650, 1},
    {"Ushortcyrillic", cp_single_651, 1},
    {"Usmall", cp_single_652, 1},
    {"Ustraightcyrillic", cp_single_653, 1},
    {"Ustraightstrokecyrillic", cp_single_654, 1},
    {"Utilde", cp_single_655, 1},
    {"Utildeacute", cp_single_656, 1},
    {"Utildebelow", cp_single_657, 1},
    {"V", cp_single_658, 1},
    {"Vcircle", cp_single_659, 1},
    {"Vdotbelow", cp_single_660, 1},
    {"Vecyrillic", cp_single_661, 1},
    {"Vewarmenian", cp_single_662, 1},
    {"Vhook", cp_single_663, 1},
    {"Vmonospace", cp_single_664, 1},
    {"Voarmenian", cp_single_665, 1},
    {"Vsmall", cp_single_666, 1},
    {"Vtilde", cp_single_667, 1},
    {"W", cp_single_668, 1},
    {"Wacute", cp_single_669, 1},
    {"Wcircle", cp_single_670, 1},
    {"Wcircumflex", cp_single_671, 1},
    {"Wdieresis", cp_single_672, 1},
    {"Wdotaccent", cp_single_673, 1},
    {"Wdotbelow", cp_single_674, 1},
    {"Wgrave", cp_single_675, 1},
    {"Wmonospace", cp_single_676, 1},
    {"Wsmall", cp_single_677, 1},
    {"X", cp_single_678, 1},
    {"Xcircle", cp_single_679, 1},
    {"Xdieresis", cp_single_680, 1},
    {"Xdotaccent", cp_single_681, 1},
    {"Xeharmenian", cp_single_682, 1},
    {"Xi", cp_single_683, 1},
    {"Xmonospace", cp_single_684, 1},
    {"Xsmall", cp_single_685, 1},
    {"Y", cp_single_686, 1},
    {"Yacute", cp_single_687, 1},
    {"Yacutesmall", cp_single_688, 1},
    {"Yatcyrillic", cp_single_689, 1},
    {"Ycircle", cp_single_690, 1},
    {"Ycircumflex", cp_single_691, 1},
    {"Ydieresis", cp_single_692, 1},
    {"Ydieresissmall", cp_single_693, 1},
    {"Ydotaccent", cp_single_694, 1},
    {"Ydotbelow", cp_single_695, 1},
    {"Yericyrillic", cp_single_696, 1},
    {"Yerudieresiscyrillic", cp_single_697, 1},
    {"Ygrave", cp_single_698, 1},
    {"Yhook", cp_single_699, 1},
    {"Yhookabove", cp_single_700, 1},
    {"Yiarmenian", cp_single_701, 1},
    {"Yicyrillic", cp_single_702, 1},
    {"Yiwnarmenian", cp_single_703, 1},
    {"Ymonospace", cp_single_704, 1},
    {"Ysmall", cp_single_705, 1},
    {"Ytilde", cp_single_706, 1},
    {"Yusbigcyrillic", cp_single_707, 1},
    {"Yusbigiotifiedcyrillic", cp_single_708, 1},
    {"Yuslittlecyrillic", cp_single_709, 1},
    {"Yuslittleiotifiedcyrillic", cp_single_710, 1},
    {"Z", cp_single_711, 1},
    {"Zaarmenian", cp_single_712, 1},
    {"Zacute", cp_single_713, 1},
    {"Zcaron", cp_single_714, 1},
    {"Zcaronsmall", cp_single_715, 1},
    {"Zcircle", cp_single_716, 1},
    {"Zcircumflex", cp_single_717, 1},
    {"Zdot", cp_single_718, 1},
    {"Zdotaccent", cp_single_719, 1},
    {"Zdotbelow", cp_single_720, 1},
    {"Zecyrillic", cp_single_721, 1},
    {"Zedescendercyrillic", cp_single_722, 1},
    {"Zedieresiscyrillic", cp_single_723, 1},
    {"Zeta", cp_single_724, 1},
    {"Zhearmenian", cp_single_725, 1},
    {"Zhebrevecyrillic", cp_single_726, 1},
    {"Zhecyrillic", cp_single_727, 1},
    {"Zhedescendercyrillic", cp_single_728, 1},
    {"Zhedieresiscyrillic", cp_single_729, 1},
    {"Zlinebelow", cp_single_730, 1},
    {"Zmonospace", cp_single_731, 1},
    {"Zsmall", cp_single_732, 1},
    {"Zstroke", cp_single_733, 1},
    {"a", cp_single_734, 1},
    {"aabengali", cp_single_735, 1},
    {"aacute", cp_single_736, 1},
    {"aadeva", cp_single_737, 1},
    {"aagujarati", cp_single_738, 1},
    {"aagurmukhi", cp_single_739, 1},
    {"aamatragurmukhi", cp_single_740, 1},
    {"aarusquare", cp_single_741, 1},
    {"aavowelsignbengali", cp_single_742, 1},
    {"aavowelsigndeva", cp_single_743, 1},
    {"aavowelsigngujarati", cp_single_744, 1},
    {"abbreviationmarkarmenian", cp_single_745, 1},
    {"abbreviationsigndeva", cp_single_746, 1},
    {"abengali", cp_single_747, 1},
    {"abopomofo", cp_single_748, 1},
    {"abreve", cp_single_749, 1},
    {"abreveacute", cp_single_750, 1},
    {"abrevecyrillic", cp_single_751, 1},
    {"abrevedotbelow", cp_single_752, 1},
    {"abrevegrave", cp_single_753, 1},
    {"abrevehookabove", cp_single_754, 1},
    {"abrevetilde", cp_single_755, 1},
    {"acaron", cp_single_756, 1},
    {"acircle", cp_single_757, 1},
    {"acircumflex", cp_single_758, 1},
    {"acircumflexacute", cp_single_759, 1},
    {"acircumflexdotbelow", cp_single_760, 1},
    {"acircumflexgrave", cp_single_761, 1},
    {"acircumflexhookabove", cp_single_762, 1},
    {"acircumflextilde", cp_single_763, 1},
    {"acute", cp_single_764, 1},
    {"acutebelowcmb", cp_single_765, 1},
    {"acutecmb", cp_single_766, 1},
    {"acutecomb", cp_single_767, 1},
    {"acutedeva", cp_single_768, 1},
    {"acutelowmod", cp_single_769, 1},
    {"acutetonecmb", cp_single_770, 1},
    {"acyrillic", cp_single_771, 1},
    {"adblgrave", cp_single_772, 1},
    {"addakgurmukhi", cp_single_773, 1},
    {"adeva", cp_single_774, 1},
    {"adieresis", cp_single_775, 1},
    {"adieresiscyrillic", cp_single_776, 1},
    {"adieresismacron", cp_single_777, 1},
    {"adotbelow", cp_single_778, 1},
    {"adotmacron", cp_single_779, 1},
    {"ae", cp_single_780, 1},
    {"aeacute", cp_single_781, 1},
    {"aekorean", cp_single_782, 1},
    {"aemacron", cp_single_783, 1},
    {"afii00208", cp_single_784, 1},
    {"afii08941", cp_single_785, 1},
    {"afii10017", cp_single_786, 1},
    {"afii10018", cp_single_787, 1},
    {"afii10019", cp_single_788, 1},
    {"afii10020", cp_single_789, 1},
    {"afii10021", cp_single_790, 1},
    {"afii10022", cp_single_791, 1},
    {"afii10023", cp_single_792, 1},
    {"afii10024", cp_single_793, 1},
    {"afii10025", cp_single_794, 1},
    {"afii10026", cp_single_795, 1},
    {"afii10027", cp_single_796, 1},
    {"afii10028", cp_single_797, 1},
    {"afii10029", cp_single_798, 1},
    {"afii10030", cp_single_799, 1},
    {"afii10031", cp_single_800, 1},
    {"afii10032", cp_single_801, 1},
    {"afii10033", cp_single_802, 1},
    {"afii10034", cp_single_803, 1},
    {"afii10035", cp_single_804, 1},
    {"afii10036", cp_single_805, 1},
    {"afii10037", cp_single_806, 1},
    {"afii10038", cp_single_807, 1},
    {"afii10039", cp_single_808, 1},
    {"afii10040", cp_single_809, 1},
    {"afii10041", cp_single_810, 1},
    {"afii10042", cp_single_811, 1},
    {"afii10043", cp_single_812, 1},
    {"afii10044", cp_single_813, 1},
    {"afii10045", cp_single_814, 1},
    {"afii10046", cp_single_815, 1},
    {"afii10047", cp_single_816, 1},
    {"afii10048", cp_single_817, 1},
    {"afii10049", cp_single_818, 1},
    {"afii10050", cp_single_819, 1},
    {"afii10051", cp_single_820, 1},
    {"afii10052", cp_single_821, 1},
    {"afii10053", cp_single_822, 1},
    {"afii10054", cp_single_823, 1},
    {"afii10055", cp_single_824, 1},
    {"afii10056", cp_single_825, 1},
    {"afii10057", cp_single_826, 1},
    {"afii10058", cp_single_827, 1},
    {"afii10059", cp_single_828, 1},
    {"afii10060", cp_single_829, 1},
    {"afii10061", cp_single_830, 1},
    {"afii10062", cp_single_831, 1},
    {"afii10063", cp_single_832, 1},
    {"afii10064", cp_single_833, 1},
    {"afii10065", cp_single_834, 1},
    {"afii10066", cp_single_835, 1},
    {"afii10067", cp_single_836, 1},
    {"afii10068", cp_single_837, 1},
    {"afii10069", cp_single_838, 1},
    {"afii10070", cp_single_839, 1},
    {"afii10071", cp_single_840, 1},
    {"afii10072", cp_single_841, 1},
    {"afii10073", cp_single_842, 1},
    {"afii10074", cp_single_843, 1},
    {"afii10075", cp_single_844, 1},
    {"afii10076", cp_single_845, 1},
    {"afii10077", cp_single_846, 1},
    {"afii10078", cp_single_847, 1},
    {"afii10079", cp_single_848, 1},
    {"afii10080", cp_single_849, 1},
    {"afii10081", cp_single_850, 1},
    {"afii10082", cp_single_851, 1},
    {"afii10083", cp_single_852, 1},
    {"afii10084", cp_single_853, 1},
    {"afii10085", cp_single_854, 1},
    {"afii10086", cp_single_855, 1},
    {"afii10087", cp_single_856, 1},
    {"afii10088", cp_single_857, 1},
    {"afii10089", cp_single_858, 1},
    {"afii10090", cp_single_859, 1},
    {"afii10091", cp_single_860, 1},
    {"afii10092", cp_single_861, 1},
    {"afii10093", cp_single_862, 1},
    {"afii10094", cp_single_863, 1},
    {"afii10095", cp_single_864, 1},
    {"afii10096", cp_single_865, 1},
    {"afii10097", cp_single_866, 1},
    {"afii10098", cp_single_867, 1},
    {"afii10099", cp_single_868, 1},
    {"afii10100", cp_single_869, 1},
    {"afii10101", cp_single_870, 1},
    {"afii10102", cp_single_871, 1},
    {"afii10103", cp_single_872, 1},
    {"afii10104", cp_single_873, 1},
    {"afii10105", cp_single_874, 1},
    {"afii10106", cp_single_875, 1},
    {"afii10107", cp_single_876, 1},
    {"afii10108", cp_single_877, 1},
    {"afii10109", cp_single_878, 1},
    {"afii10110", cp_single_879, 1},
    {"afii10145", cp_single_880, 1},
    {"afii10146", cp_single_881, 1},
    {"afii10147", cp_single_882, 1},
    {"afii10148", cp_single_883, 1},
    {"afii10192", cp_single_884, 1},
    {"afii10193", cp_single_885, 1},
    {"afii10194", cp_single_886, 1},
    {"afii10195", cp_single_887, 1},
    {"afii10196", cp_single_888, 1},
    {"afii10831", cp_single_889, 1},
    {"afii10832", cp_single_890, 1},
    {"afii10846", cp_single_891, 1},
    {"afii299", cp_single_892, 1},
    {"afii300", cp_single_893, 1},
    {"afii301", cp_single_894, 1},
    {"afii57381", cp_single_895, 1},
    {"afii57388", cp_single_896, 1},
    {"afii57392", cp_single_897, 1},
    {"afii57393", cp_single_898, 1},
    {"afii57394", cp_single_899, 1},
    {"afii57395", cp_single_900, 1},
    {"afii57396", cp_single_901, 1},
    {"afii57397", cp_single_902, 1},
    {"afii57398", cp_single_903, 1},
    {"afii57399", cp_single_904, 1},
    {"afii57400", cp_single_905, 1},
    {"afii57401", cp_single_906, 1},
    {"afii57403", cp_single_907, 1},
    {"afii57407", cp_single_908, 1},
    {"afii57409", cp_single_909, 1},
    {"afii57410", cp_single_910, 1},
    {"afii57411", cp_single_911, 1},
    {"afii57412", cp_single_912, 1},
    {"afii57413", cp_single_913, 1},
    {"afii57414", cp_single_914, 1},
    {"afii57415", cp_single_915, 1},
    {"afii57416", cp_single_916, 1},
    {"afii57417", cp_single_917, 1},
    {"afii57418", cp_single_918, 1},
    {"afii57419", cp_single_919, 1},
    {"afii57420", cp_single_920, 1},
    {"afii57421", cp_single_921, 1},
    {"afii57422", cp_single_922, 1},
    {"afii57423", cp_single_923, 1},
    {"afii57424", cp_single_924, 1},
    {"afii57425", cp_single_925, 1},
    {"afii57426", cp_single_926, 1},
    {"afii57427", cp_single_927, 1},
    {"afii57428", cp_single_928, 1},
    {"afii57429", cp_single_929, 1},
    {"afii57430", cp_single_930, 1},
    {"afii57431", cp_single_931, 1},
    {"afii57432", cp_single_932, 1},
    {"afii57433", cp_single_933, 1},
    {"afii57434", cp_single_934, 1},
    {"afii57440", cp_single_935, 1},
    {"afii57441", cp_single_936, 1},
    {"afii57442", cp_single_937, 1},
    {"afii57443", cp_single_938, 1},
    {"afii57444", cp_single_939, 1},
    {"afii57445", cp_single_940, 1},
    {"afii57446", cp_single_941, 1},
    {"afii57448", cp_single_942, 1},
    {"afii57449", cp_single_943, 1},
    {"afii57450", cp_single_944, 1},
    {"afii57451", cp_single_945, 1},
    {"afii57452", cp_single_946, 1},
    {"afii57453", cp_single_947, 1},
    {"afii57454", cp_single_948, 1},
    {"afii57455", cp_single_949, 1},
    {"afii57456", cp_single_950, 1},
    {"afii57457", cp_single_951, 1},
    {"afii57458", cp_single_952, 1},
    {"afii57470", cp_single_953, 1},
    {"afii57505", cp_single_954, 1},
    {"afii57506", cp_single_955, 1},
    {"afii57507", cp_single_956, 1},
    {"afii57508", cp_single_957, 1},
    {"afii57509", cp_single_958, 1},
    {"afii57511", cp_single_959, 1},
    {"afii57512", cp_single_960, 1},
    {"afii57513", cp_single_961, 1},
    {"afii57514", cp_single_962, 1},
    {"afii57519", cp_single_963, 1},
    {"afii57534", cp_single_964, 1},
    {"afii57636", cp_single_965, 1},
    {"afii57645", cp_single_966, 1},
    {"afii57658", cp_single_967, 1},
    {"afii57664", cp_single_968, 1},
    {"afii57665", cp_single_969, 1},
    {"afii57666", cp_single_970, 1},
    {"afii57667", cp_single_971, 1},
    {"afii57668", cp_single_972, 1},
    {"afii57669", cp_single_973, 1},
    {"afii57670", cp_single_974, 1},
    {"afii57671", cp_single_975, 1},
    {"afii57672", cp_single_976, 1},
    {"afii57673", cp_single_977, 1},
    {"afii57674", cp_single_978, 1},
    {"afii57675", cp_single_979, 1},
    {"afii57676", cp_single_980, 1},
    {"afii57677", cp_single_981, 1},
    {"afii57678", cp_single_982, 1},
    {"afii57679", cp_single_983, 1},
    {"afii57680", cp_single_984, 1},
    {"afii57681", cp_single_985, 1},
    {"afii57682", cp_single_986, 1},
    {"afii57683", cp_single_987, 1},
    {"afii57684", cp_single_988, 1},
    {"afii57685", cp_single_989, 1},
    {"afii57686", cp_single_990, 1},
    {"afii57687", cp_single_991, 1},
    {"afii57688", cp_single_992, 1},
    {"afii57689", cp_single_993, 1},
    {"afii57690", cp_single_994, 1},
    {"afii57694", cp_single_995, 1},
    {"afii57695", cp_single_996, 1},
    {"afii57700", cp_single_997, 1},
    {"afii57705", cp_single_998, 1},
    {"afii57716", cp_single_999, 1},
    {"afii57717", cp_single_1000, 1},
    {"afii57718", cp_single_1001, 1},
    {"afii57723", cp_single_1002, 1},
    {"afii57793", cp_single_1003, 1},
    {"afii57794", cp_single_1004, 1},
    {"afii57795", cp_single_1005, 1},
    {"afii57796", cp_single_1006, 1},
    {"afii57797", cp_single_1007, 1},
    {"afii57798", cp_single_1008, 1},
    {"afii57799", cp_single_1009, 1},
    {"afii57800", cp_single_1010, 1},
    {"afii57801", cp_single_1011, 1},
    {"afii57802", cp_single_1012, 1},
    {"afii57803", cp_single_1013, 1},
    {"afii57804", cp_single_1014, 1},
    {"afii57806", cp_single_1015, 1},
    {"afii57807", cp_single_1016, 1},
    {"afii57839", cp_single_1017, 1},
    {"afii57841", cp_single_1018, 1},
    {"afii57842", cp_single_1019, 1},
    {"afii57929", cp_single_1020, 1},
    {"afii61248", cp_single_1021, 1},
    {"afii61289", cp_single_1022, 1},
    {"afii61352", cp_single_1023, 1},
    {"afii61573", cp_single_1024, 1},
    {"afii61574", cp_single_1025, 1},
    {"afii61575", cp_single_1026, 1},
    {"afii61664", cp_single_1027, 1},
    {"afii63167", cp_single_1028, 1},
    {"afii64937", cp_single_1029, 1},
    {"agrave", cp_single_1030, 1},
    {"agujarati", cp_single_1031, 1},
    {"agurmukhi", cp_single_1032, 1},
    {"ahiragana", cp_single_1033, 1},
    {"ahookabove", cp_single_1034, 1},
    {"aibengali", cp_single_1035, 1},
    {"aibopomofo", cp_single_1036, 1},
    {"aideva", cp_single_1037, 1},
    {"aiecyrillic", cp_single_1038, 1},
    {"aigujarati", cp_single_1039, 1},
    {"aigurmukhi", cp_single_1040, 1},
    {"aimatragurmukhi", cp_single_1041, 1},
    {"ainarabic", cp_single_1042, 1},
    {"ainfinalarabic", cp_single_1043, 1},
    {"aininitialarabic", cp_single_1044, 1},
    {"ainmedialarabic", cp_single_1045, 1},
    {"ainvertedbreve", cp_single_1046, 1},
    {"aivowelsignbengali", cp_single_1047, 1},
    {"aivowelsigndeva", cp_single_1048, 1},
    {"aivowelsigngujarati", cp_single_1049, 1},
    {"akatakana", cp_single_1050, 1},
    {"akatakanahalfwidth", cp_single_1051, 1},
    {"akorean", cp_single_1052, 1},
    {"alef", cp_single_1053, 1},
    {"alefarabic", cp_single_1054, 1},
    {"alefdageshhebrew", cp_single_1055, 1},
    {"aleffinalarabic", cp_single_1056, 1},
    {"alefhamzaabovearabic", cp_single_1057, 1},
    {"alefhamzaabovefinalarabic", cp_single_1058, 1},
    {"alefhamzabelowarabic", cp_single_1059, 1},
    {"alefhamzabelowfinalarabic", cp_single_1060, 1},
    {"alefhebrew", cp_single_1061, 1},
    {"aleflamedhebrew", cp_single_1062, 1},
    {"alefmaddaabovearabic", cp_single_1063, 1},
    {"alefmaddaabovefinalarabic", cp_single_1064, 1},
    {"alefmaksuraarabic", cp_single_1065, 1},
    {"alefmaksurafinalarabic", cp_single_1066, 1},
    {"alefmaksurainitialarabic", cp_single_1067, 1},
    {"alefmaksuramedialarabic", cp_single_1068, 1},
    {"alefpatahhebrew", cp_single_1069, 1},
    {"alefqamatshebrew", cp_single_1070, 1},
    {"aleph", cp_single_1071, 1},
    {"allequal", cp_single_1072, 1},
    {"alpha", cp_single_1073, 1},
    {"alphatonos", cp_single_1074, 1},
    {"amacron", cp_single_1075, 1},
    {"amonospace", cp_single_1076, 1},
    {"ampersand", cp_single_1077, 1},
    {"ampersandmonospace", cp_single_1078, 1},
    {"ampersandsmall", cp_single_1079, 1},
    {"amsquare", cp_single_1080, 1},
    {"anbopomofo", cp_single_1081, 1},
    {"angbopomofo", cp_single_1082, 1},
    {"angkhankhuthai", cp_single_1083, 1},
    {"angle", cp_single_1084, 1},
    {"anglebracketleft", cp_single_1085, 1},
    {"anglebracketleftvertical", cp_single_1086, 1},
    {"anglebracketright", cp_single_1087, 1},
    {"anglebracketrightvertical", cp_single_1088, 1},
    {"angleleft", cp_single_1089, 1},
    {"angleright", cp_single_1090, 1},
    {"angstrom", cp_single_1091, 1},
    {"anoteleia", cp_single_1092, 1},
    {"anudattadeva", cp_single_1093, 1},
    {"anusvarabengali", cp_single_1094, 1},
    {"anusvaradeva", cp_single_1095, 1},
    {"anusvaragujarati", cp_single_1096, 1},
    {"aogonek", cp_single_1097, 1},
    {"apaatosquare", cp_single_1098, 1},
    {"aparen", cp_single_1099, 1},
    {"apostrophearmenian", cp_single_1100, 1},
    {"apostrophemod", cp_single_1101, 1},
    {"apple", cp_single_1102, 1},
    {"approaches", cp_single_1103, 1},
    {"approxequal", cp_single_1104, 1},
    {"approxequalorimage", cp_single_1105, 1},
    {"approximatelyequal", cp_single_1106, 1},
    {"araeaekorean", cp_single_1107, 1},
    {"araeakorean", cp_single_1108, 1},
    {"arc", cp_single_1109, 1},
    {"arighthalfring", cp_single_1110, 1},
    {"aring", cp_single_1111, 1},
    {"aringacute", cp_single_1112, 1},
    {"aringbelow", cp_single_1113, 1},
    {"arrowboth", cp_single_1114, 1},
    {"arrowdashdown", cp_single_1115, 1},
    {"arrowdashleft", cp_single_1116, 1},
    {"arrowdashright", cp_single_1117, 1},
    {"arrowdashup", cp_single_1118, 1},
    {"arrowdblboth", cp_single_1119, 1},
    {"arrowdbldown", cp_single_1120, 1},
    {"arrowdblleft", cp_single_1121, 1},
    {"arrowdblright", cp_single_1122, 1},
    {"arrowdblup", cp_single_1123, 1},
    {"arrowdown", cp_single_1124, 1},
    {"arrowdownleft", cp_single_1125, 1},
    {"arrowdownright", cp_single_1126, 1},
    {"arrowdownwhite", cp_single_1127, 1},
    {"arrowheaddownmod", cp_single_1128, 1},
    {"arrowheadleftmod", cp_single_1129, 1},
    {"arrowheadrightmod", cp_single_1130, 1},
    {"arrowheadupmod", cp_single_1131, 1},
    {"arrowhorizex", cp_single_1132, 1},
    {"arrowleft", cp_single_1133, 1},
    {"arrowleftdbl", cp_single_1134, 1},
    {"arrowleftdblstroke", cp_single_1135, 1},
    {"arrowleftoverright", cp_single_1136, 1},
    {"arrowleftwhite", cp_single_1137, 1},
    {"arrowright", cp_single_1138, 1},
    {"arrowrightdblstroke", cp_single_1139, 1},
    {"arrowrightheavy", cp_single_1140, 1},
    {"arrowrightoverleft", cp_single_1141, 1},
    {"arrowrightwhite", cp_single_1142, 1},
    {"arrowtableft", cp_single_1143, 1},
    {"arrowtabright", cp_single_1144, 1},
    {"arrowup", cp_single_1145, 1},
    {"arrowupdn", cp_single_1146, 1},
    {"arrowupdnbse", cp_single_1147, 1},
    {"arrowupdownbase", cp_single_1148, 1},
    {"arrowupleft", cp_single_1149, 1},
    {"arrowupleftofdown", cp_single_1150, 1},
    {"arrowupright", cp_single_1151, 1},
    {"arrowupwhite", cp_single_1152, 1},
    {"arrowvertex", cp_single_1153, 1},
    {"asciicircum", cp_single_1154, 1},
    {"asciicircummonospace", cp_single_1155, 1},
    {"asciitilde", cp_single_1156, 1},
    {"asciitildemonospace", cp_single_1157, 1},
    {"ascript", cp_single_1158, 1},
    {"ascriptturned", cp_single_1159, 1},
    {"asmallhiragana", cp_single_1160, 1},
    {"asmallkatakana", cp_single_1161, 1},
    {"asmallkatakanahalfwidth", cp_single_1162, 1},
    {"asterisk", cp_single_1163, 1},
    {"asteriskaltonearabic", cp_single_1164, 1},
    {"asteriskarabic", cp_single_1165, 1},
    {"asteriskmath", cp_single_1166, 1},
    {"asteriskmonospace", cp_single_1167, 1},
    {"asterisksmall", cp_single_1168, 1},
    {"asterism", cp_single_1169, 1},
    {"asuperior", cp_single_1170, 1},
    {"asymptoticallyequal", cp_single_1171, 1},
    {"at", cp_single_1172, 1},
    {"atilde", cp_single_1173, 1},
    {"atmonospace", cp_single_1174, 1},
    {"atsmall", cp_single_1175, 1},
    {"aturned", cp_single_1176, 1},
    {"aubengali", cp_single_1177, 1},
    {"aubopomofo", cp_single_1178, 1},
    {"audeva", cp_single_1179, 1},
    {"augujarati", cp_single_1180, 1},
    {"augurmukhi", cp_single_1181, 1},
    {"aulengthmarkbengali", cp_single_1182, 1},
    {"aumatragurmukhi", cp_single_1183, 1},
    {"auvowelsignbengali", cp_single_1184, 1},
    {"auvowelsigndeva", cp_single_1185, 1},
    {"auvowelsigngujarati", cp_single_1186, 1},
    {"avagrahadeva", cp_single_1187, 1},
    {"aybarmenian", cp_single_1188, 1},
    {"ayin", cp_single_1189, 1},
    {"ayinaltonehebrew", cp_single_1190, 1},
    {"ayinhebrew", cp_single_1191, 1},
    {"b", cp_single_1192, 1},
    {"babengali", cp_single_1193, 1},
    {"backslash", cp_single_1194, 1},
    {"backslashmonospace", cp_single_1195, 1},
    {"badeva", cp_single_1196, 1},
    {"bagujarati", cp_single_1197, 1},
    {"bagurmukhi", cp_single_1198, 1},
    {"bahiragana", cp_single_1199, 1},
    {"bahtthai", cp_single_1200, 1},
    {"bakatakana", cp_single_1201, 1},
    {"bar", cp_single_1202, 1},
    {"barmonospace", cp_single_1203, 1},
    {"bbopomofo", cp_single_1204, 1},
    {"bcircle", cp_single_1205, 1},
    {"bdotaccent", cp_single_1206, 1},
    {"bdotbelow", cp_single_1207, 1},
    {"beamedsixteenthnotes", cp_single_1208, 1},
    {"because", cp_single_1209, 1},
    {"becyrillic", cp_single_1210, 1},
    {"beharabic", cp_single_1211, 1},
    {"behfinalarabic", cp_single_1212, 1},
    {"behinitialarabic", cp_single_1213, 1},
    {"behiragana", cp_single_1214, 1},
    {"behmedialarabic", cp_single_1215, 1},
    {"behmeeminitialarabic", cp_single_1216, 1},
    {"behmeemisolatedarabic", cp_single_1217, 1},
    {"behnoonfinalarabic", cp_single_1218, 1},
    {"bekatakana", cp_single_1219, 1},
    {"benarmenian", cp_single_1220, 1},
    {"bet", cp_single_1221, 1},
    {"beta", cp_single_1222, 1},
    {"betasymbolgreek", cp_single_1223, 1},
    {"betdagesh", cp_single_1224, 1},
    {"betdageshhebrew", cp_single_1225, 1},
    {"bethebrew", cp_single_1226, 1},
    {"betrafehebrew", cp_single_1227, 1},
    {"bhabengali", cp_single_1228, 1},
    {"bhadeva", cp_single_1229, 1},
    {"bhagujarati", cp_single_1230, 1},
    {"bhagurmukhi", cp_single_1231, 1},
    {"bhook", cp_single_1232, 1},
    {"bihiragana", cp_single_1233, 1},
    {"bikatakana", cp_single_1234, 1},
    {"bilabialclick", cp_single_1235, 1},
    {"bindigurmukhi", cp_single_1236, 1},
    {"birusquare", cp_single_1237, 1},
    {"blackcircle", cp_single_1238, 1},
    {"blackdiamond", cp_single_1239, 1},
    {"blackdownpointingtriangle", cp_single_1240, 1},
    {"blackleftpointingpointer", cp_single_1241, 1},
    {"blackleftpointingtriangle", cp_single_1242, 1},
    {"blacklenticularbracketleft", cp_single_1243, 1},
    {"blacklenticularbracketleftvertical", cp_single_1244, 1},
    {"blacklenticularbracketright", cp_single_1245, 1},
    {"blacklenticularbracketrightvertical", cp_single_1246, 1},
    {"blacklowerlefttriangle", cp_single_1247, 1},
    {"blacklowerrighttriangle", cp_single_1248, 1},
    {"blackrectangle", cp_single_1249, 1},
    {"blackrightpointingpointer", cp_single_1250, 1},
    {"blackrightpointingtriangle", cp_single_1251, 1},
    {"blacksmallsquare", cp_single_1252, 1},
    {"blacksmilingface", cp_single_1253, 1},
    {"blacksquare", cp_single_1254, 1},
    {"blackstar", cp_single_1255, 1},
    {"blackupperlefttriangle", cp_single_1256, 1},
    {"blackupperrighttriangle", cp_single_1257, 1},
    {"blackuppointingsmalltriangle", cp_single_1258, 1},
    {"blackuppointingtriangle", cp_single_1259, 1},
    {"blank", cp_single_1260, 1},
    {"blinebelow", cp_single_1261, 1},
    {"block", cp_single_1262, 1},
    {"bmonospace", cp_single_1263, 1},
    {"bobaimaithai", cp_single_1264, 1},
    {"bohiragana", cp_single_1265, 1},
    {"bokatakana", cp_single_1266, 1},
    {"bparen", cp_single_1267, 1},
    {"bqsquare", cp_single_1268, 1},
    {"braceex", cp_single_1269, 1},
    {"braceleft", cp_single_1270, 1},
    {"braceleftbt", cp_single_1271, 1},
    {"braceleftmid", cp_single_1272, 1},
    {"braceleftmonospace", cp_single_1273, 1},
    {"braceleftsmall", cp_single_1274, 1},
    {"bracelefttp", cp_single_1275, 1},
    {"braceleftvertical", cp_single_1276, 1},
    {"braceright", cp_single_1277, 1},
    {"bracerightbt", cp_single_1278, 1},
    {"bracerightmid", cp_single_1279, 1},
    {"bracerightmonospace", cp_single_1280, 1},
    {"bracerightsmall", cp_single_1281, 1},
    {"bracerighttp", cp_single_1282, 1},
    {"bracerightvertical", cp_single_1283, 1},
    {"bracketleft", cp_single_1284, 1},
    {"bracketleftbt", cp_single_1285, 1},
    {"bracketleftex", cp_single_1286, 1},
    {"bracketleftmonospace", cp_single_1287, 1},
    {"bracketlefttp", cp_single_1288, 1},
    {"bracketright", cp_single_1289, 1},
    {"bracketrightbt", cp_single_1290, 1},
    {"bracketrightex", cp_single_1291, 1},
    {"bracketrightmonospace", cp_single_1292, 1},
    {"bracketrighttp", cp_single_1293, 1},
    {"breve", cp_single_1294, 1},
    {"brevebelowcmb", cp_single_1295, 1},
    {"brevecmb", cp_single_1296, 1},
    {"breveinvertedbelowcmb", cp_single_1297, 1},
    {"breveinvertedcmb", cp_single_1298, 1},
    {"breveinverteddoublecmb", cp_single_1299, 1},
    {"bridgebelowcmb", cp_single_1300, 1},
    {"bridgeinvertedbelowcmb", cp_single_1301, 1},
    {"brokenbar", cp_single_1302, 1},
    {"bstroke", cp_single_1303, 1},
    {"bsuperior", cp_single_1304, 1},
    {"btopbar", cp_single_1305, 1},
    {"buhiragana", cp_single_1306, 1},
    {"bukatakana", cp_single_1307, 1},
    {"bullet", cp_single_1308, 1},
    {"bulletinverse", cp_single_1309, 1},
    {"bulletoperator", cp_single_1310, 1},
    {"bullseye", cp_single_1311, 1},
    {"c", cp_single_1312, 1},
    {"caarmenian", cp_single_1313, 1},
    {"cabengali", cp_single_1314, 1},
    {"cacute", cp_single_1315, 1},
    {"cadeva", cp_single_1316, 1},
    {"cagujarati", cp_single_1317, 1},
    {"cagurmukhi", cp_single_1318, 1},
    {"calsquare", cp_single_1319, 1},
    {"candrabindubengali", cp_single_1320, 1},
    {"candrabinducmb", cp_single_1321, 1},
    {"candrabindudeva", cp_single_1322, 1},
    {"candrabindugujarati", cp_single_1323, 1},
    {"capslock", cp_single_1324, 1},
    {"careof", cp_single_1325, 1},
    {"caron", cp_single_1326, 1},
    {"caronbelowcmb", cp_single_1327, 1},
    {"caroncmb", cp_single_1328, 1},
    {"carriagereturn", cp_single_1329, 1},
    {"cbopomofo", cp_single_1330, 1},
    {"ccaron", cp_single_1331, 1},
    {"ccedilla", cp_single_1332, 1},
    {"ccedillaacute", cp_single_1333, 1},
    {"ccircle", cp_single_1334, 1},
    {"ccircumflex", cp_single_1335, 1},
    {"ccurl", cp_single_1336, 1},
    {"cdot", cp_single_1337, 1},
    {"cdotaccent", cp_single_1338, 1},
    {"cdsquare", cp_single_1339, 1},
    {"cedilla", cp_single_1340, 1},
    {"cedillacmb", cp_single_1341, 1},
    {"cent", cp_single_1342, 1},
    {"centigrade", cp_single_1343, 1},
    {"centinferior", cp_single_1344, 1},
    {"centmonospace", cp_single_1345, 1},
    {"centoldstyle", cp_single_1346, 1},
    {"centsuperior", cp_single_1347, 1},
    {"chaarmenian", cp_single_1348, 1},
    {"chabengali", cp_single_1349, 1},
    {"chadeva", cp_single_1350, 1},
    {"chagujarati", cp_single_1351, 1},
    {"chagurmukhi", cp_single_1352, 1},
    {"chbopomofo", cp_single_1353, 1},
    {"cheabkhasiancyrillic", cp_single_1354, 1},
    {"checkmark", cp_single_1355, 1},
    {"checyrillic", cp_single_1356, 1},
    {"chedescenderabkhasiancyrillic", cp_single_1357, 1},
    {"chedescendercyrillic", cp_single_1358, 1},
    {"chedieresiscyrillic", cp_single_1359, 1},
    {"cheharmenian", cp_single_1360, 1},
    {"chekhakassiancyrillic", cp_single_1361, 1},
    {"cheverticalstrokecyrillic", cp_single_1362, 1},
    {"chi", cp_single_1363, 1},
    {"chieuchacirclekorean", cp_single_1364, 1},
    {"chieuchaparenkorean", cp_single_1365, 1},
    {"chieuchcirclekorean", cp_single_1366, 1},
    {"chieuchkorean", cp_single_1367, 1},
    {"chieuchparenkorean", cp_single_1368, 1},
    {"chochangthai", cp_single_1369, 1},
    {"chochanthai", cp_single_1370, 1},
    {"chochingthai", cp_single_1371, 1},
    {"chochoethai", cp_single_1372, 1},
    {"chook", cp_single_1373, 1},
    {"cieucacirclekorean", cp_single_1374, 1},
    {"cieucaparenkorean", cp_single_1375, 1},
    {"cieuccirclekorean", cp_single_1376, 1},
    {"cieuckorean", cp_single_1377, 1},
    {"cieucparenkorean", cp_single_1378, 1},
    {"cieucuparenkorean", cp_single_1379, 1},
    {"circle", cp_single_1380, 1},
    {"circlemultiply", cp_single_1381, 1},
    {"circleot", cp_single_1382, 1},
    {"circleplus", cp_single_1383, 1},
    {"circlepostalmark", cp_single_1384, 1},
    {"circlewithlefthalfblack", cp_single_1385, 1},
    {"circlewithrighthalfblack", cp_single_1386, 1},
    {"circumflex", cp_single_1387, 1},
    {"circumflexbelowcmb", cp_single_1388, 1},
    {"circumflexcmb", cp_single_1389, 1},
    {"clear", cp_single_1390, 1},
    {"clickalveolar", cp_single_1391, 1},
    {"clickdental", cp_single_1392, 1},
    {"clicklateral", cp_single_1393, 1},
    {"clickretroflex", cp_single_1394, 1},
    {"club", cp_single_1395, 1},
    {"clubsuitblack", cp_single_1396, 1},
    {"clubsuitwhite", cp_single_1397, 1},
    {"cmcubedsquare", cp_single_1398, 1},
    {"cmonospace", cp_single_1399, 1},
    {"cmsquaredsquare", cp_single_1400, 1},
    {"coarmenian", cp_single_1401, 1},
    {"colon", cp_single_1402, 1},
    {"colonmonetary", cp_single_1403, 1},
    {"colonmonospace", cp_single_1404, 1},
    {"colonsign", cp_single_1405, 1},
    {"colonsmall", cp_single_1406, 1},
    {"colontriangularhalfmod", cp_single_1407, 1},
    {"colontriangularmod", cp_single_1408, 1},
    {"comma", cp_single_1409, 1},
    {"commaabovecmb", cp_single_1410, 1},
    {"commaaboverightcmb", cp_single_1411, 1},
    {"commaaccent", cp_single_1412, 1},
    {"commaarabic", cp_single_1413, 1},
    {"commaarmenian", cp_single_1414, 1},
    {"commainferior", cp_single_1415, 1},
    {"commamonospace", cp_single_1416, 1},
    {"commareversedabovecmb", cp_single_1417, 1},
    {"commareversedmod", cp_single_1418, 1},
    {"commasmall", cp_single_1419, 1},
    {"commasuperior", cp_single_1420, 1},
    {"commaturnedabovecmb", cp_single_1421, 1},
    {"commaturnedmod", cp_single_1422, 1},
    {"compass", cp_single_1423, 1},
    {"congruent", cp_single_1424, 1},
    {"contourintegral", cp_single_1425, 1},
    {"control", cp_single_1426, 1},
    {"controlACK", cp_single_1427, 1},
    {"controlBEL", cp_single_1428, 1},
    {"controlBS", cp_single_1429, 1},
    {"controlCAN", cp_single_1430, 1},
    {"controlCR", cp_single_1431, 1},
    {"controlDC1", cp_single_1432, 1},
    {"controlDC2", cp_single_1433, 1},
    {"controlDC3", cp_single_1434, 1},
    {"controlDC4", cp_single_1435, 1},
    {"controlDEL", cp_single_1436, 1},
    {"controlDLE", cp_single_1437, 1},
    {"controlEM", cp_single_1438, 1},
    {"controlENQ", cp_single_1439, 1},
    {"controlEOT", cp_single_1440, 1},
    {"controlESC", cp_single_1441, 1},
    {"controlETB", cp_single_1442, 1},
    {"controlETX", cp_single_1443, 1},
    {"controlFF", cp_single_1444, 1},
    {"controlFS", cp_single_1445, 1},
    {"controlGS", cp_single_1446, 1},
    {"controlHT", cp_single_1447, 1},
    {"controlLF", cp_single_1448, 1},
    {"controlNAK", cp_single_1449, 1},
    {"controlRS", cp_single_1450, 1},
    {"controlSI", cp_single_1451, 1},
    {"controlSO", cp_single_1452, 1},
    {"controlSOT", cp_single_1453, 1},
    {"controlSTX", cp_single_1454, 1},
    {"controlSUB", cp_single_1455, 1},
    {"controlSYN", cp_single_1456, 1},
    {"controlUS", cp_single_1457, 1},
    {"controlVT", cp_single_1458, 1},
    {"copyright", cp_single_1459, 1},
    {"copyrightsans", cp_single_1460, 1},
    {"copyrightserif", cp_single_1461, 1},
    {"cornerbracketleft", cp_single_1462, 1},
    {"cornerbracketlefthalfwidth", cp_single_1463, 1},
    {"cornerbracketleftvertical", cp_single_1464, 1},
    {"cornerbracketright", cp_single_1465, 1},
    {"cornerbracketrighthalfwidth", cp_single_1466, 1},
    {"cornerbracketrightvertical", cp_single_1467, 1},
    {"corporationsquare", cp_single_1468, 1},
    {"cosquare", cp_single_1469, 1},
    {"coverkgsquare", cp_single_1470, 1},
    {"cparen", cp_single_1471, 1},
    {"cruzeiro", cp_single_1472, 1},
    {"cstretched", cp_single_1473, 1},
    {"curlyand", cp_single_1474, 1},
    {"curlyor", cp_single_1475, 1},
    {"currency", cp_single_1476, 1},
    {"cyrBreve", cp_single_1477, 1},
    {"cyrFlex", cp_single_1478, 1},
    {"cyrbreve", cp_single_1479, 1},
    {"cyrflex", cp_single_1480, 1},
    {"d", cp_single_1481, 1},
    {"daarmenian", cp_single_1482, 1},
    {"dabengali", cp_single_1483, 1},
    {"dadarabic", cp_single_1484, 1},
    {"dadeva", cp_single_1485, 1},
    {"dadfinalarabic", cp_single_1486, 1},
    {"dadinitialarabic", cp_single_1487, 1},
    {"dadmedialarabic", cp_single_1488, 1},
    {"dagesh", cp_single_1489, 1},
    {"dageshhebrew", cp_single_1490, 1},
    {"dagger", cp_single_1491, 1},
    {"daggerdbl", cp_single_1492, 1},
    {"dagujarati", cp_single_1493, 1},
    {"dagurmukhi", cp_single_1494, 1},
    {"dahiragana", cp_single_1495, 1},
    {"dakatakana", cp_single_1496, 1},
    {"dalarabic", cp_single_1497, 1},
    {"dalet", cp_single_1498, 1},
    {"daletdagesh", cp_single_1499, 1},
    {"daletdageshhebrew", cp_single_1500, 1},
    {"dalethatafpatah", cp_1501, 2},
    {"dalethatafpatahhebrew", cp_1502, 2},
    {"dalethatafsegol", cp_1503, 2},
    {"dalethatafsegolhebrew", cp_1504, 2},
    {"dalethebrew", cp_single_1501, 1},
    {"dalethiriq", cp_1506, 2},
    {"dalethiriqhebrew", cp_1507, 2},
    {"daletholam", cp_1508, 2},
    {"daletholamhebrew", cp_1509, 2},
    {"daletpatah", cp_1510, 2},
    {"daletpatahhebrew", cp_1511, 2},
    {"daletqamats", cp_1512, 2},
    {"daletqamatshebrew", cp_1513, 2},
    {"daletqubuts", cp_1514, 2},
    {"daletqubutshebrew", cp_1515, 2},
    {"daletsegol", cp_1516, 2},
    {"daletsegolhebrew", cp_1517, 2},
    {"daletsheva", cp_1518, 2},
    {"daletshevahebrew", cp_1519, 2},
    {"dalettsere", cp_1520, 2},
    {"dalettserehebrew", cp_1521, 2},
    {"dalfinalarabic", cp_single_1502, 1},
    {"dammaarabic", cp_single_1503, 1},
    {"dammalowarabic", cp_single_1504, 1},
    {"dammatanaltonearabic", cp_single_1505, 1},
    {"dammatanarabic", cp_single_1506, 1},
    {"danda", cp_single_1507, 1},
    {"dargahebrew", cp_single_1508, 1},
    {"dargalefthebrew", cp_single_1509, 1},
    {"dasiapneumatacyrilliccmb", cp_single_1510, 1},
    {"dblGrave", cp_single_1511, 1},
    {"dblanglebracketleft", cp_single_1512, 1},
    {"dblanglebracketleftvertical", cp_single_1513, 1},
    {"dblanglebracketright", cp_single_1514, 1},
    {"dblanglebracketrightvertical", cp_single_1515, 1},
    {"dblarchinvertedbelowcmb", cp_single_1516, 1},
    {"dblarrowleft", cp_single_1517, 1},
    {"dblarrowright", cp_single_1518, 1},
    {"dbldanda", cp_single_1519, 1},
    {"dblgrave", cp_single_1520, 1},
    {"dblgravecmb", cp_single_1521, 1},
    {"dblintegral", cp_single_1522, 1},
    {"dbllowline", cp_single_1523, 1},
    {"dbllowlinecmb", cp_single_1524, 1},
    {"dbloverlinecmb", cp_single_1525, 1},
    {"dblprimemod", cp_single_1526, 1},
    {"dblverticalbar", cp_single_1527, 1},
    {"dblverticallineabovecmb", cp_single_1528, 1},
    {"dbopomofo", cp_single_1529, 1},
    {"dbsquare", cp_single_1530, 1},
    {"dcaron", cp_single_1531, 1},
    {"dcedilla", cp_single_1532, 1},
    {"dcircle", cp_single_1533, 1},
    {"dcircumflexbelow", cp_single_1534, 1},
    {"dcroat", cp_single_1535, 1},
    {"ddabengali", cp_single_1536, 1},
    {"ddadeva", cp_single_1537, 1},
    {"ddagujarati", cp_single_1538, 1},
    {"ddagurmukhi", cp_single_1539, 1},
    {"ddalarabic", cp_single_1540, 1},
    {"ddalfinalarabic", cp_single_1541, 1},
    {"dddhadeva", cp_single_1542, 1},
    {"ddhabengali", cp_single_1543, 1},
    {"ddhadeva", cp_single_1544, 1},
    {"ddhagujarati", cp_single_1545, 1},
    {"ddhagurmukhi", cp_single_1546, 1},
    {"ddotaccent", cp_single_1547, 1},
    {"ddotbelow", cp_single_1548, 1},
    {"decimalseparatorarabic", cp_single_1549, 1},
    {"decimalseparatorpersian", cp_single_1550, 1},
    {"decyrillic", cp_single_1551, 1},
    {"degree", cp_single_1552, 1},
    {"dehihebrew", cp_single_1553, 1},
    {"dehiragana", cp_single_1554, 1},
    {"deicoptic", cp_single_1555, 1},
    {"dekatakana", cp_single_1556, 1},
    {"deleteleft", cp_single_1557, 1},
    {"deleteright", cp_single_1558, 1},
    {"delta", cp_single_1559, 1},
    {"deltaturned", cp_single_1560, 1},
    {"denominatorminusonenumeratorbengali", cp_single_1561, 1},
    {"dezh", cp_single_1562, 1},
    {"dhabengali", cp_single_1563, 1},
    {"dhadeva", cp_single_1564, 1},
    {"dhagujarati", cp_single_1565, 1},
    {"dhagurmukhi", cp_single_1566, 1},
    {"dhook", cp_single_1567, 1},
    {"dialytikatonos", cp_single_1568, 1},
    {"dialytikatonoscmb", cp_single_1569, 1},
    {"diamond", cp_single_1570, 1},
    {"diamondsuitwhite", cp_single_1571, 1},
    {"dieresis", cp_single_1572, 1},
    {"dieresisacute", cp_single_1573, 1},
    {"dieresisbelowcmb", cp_single_1574, 1},
    {"dieresiscmb", cp_single_1575, 1},
    {"dieresisgrave", cp_single_1576, 1},
    {"dieresistonos", cp_single_1577, 1},
    {"dihiragana", cp_single_1578, 1},
    {"dikatakana", cp_single_1579, 1},
    {"dittomark", cp_single_1580, 1},
    {"divide", cp_single_1581, 1},
    {"divides", cp_single_1582, 1},
    {"divisionslash", cp_single_1583, 1},
    {"djecyrillic", cp_single_1584, 1},
    {"dkshade", cp_single_1585, 1},
    {"dlinebelow", cp_single_1586, 1},
    {"dlsquare", cp_single_1587, 1},
    {"dmacron", cp_single_1588, 1},
    {"dmonospace", cp_single_1589, 1},
    {"dnblock", cp_single_1590, 1},
    {"dochadathai", cp_single_1591, 1},
    {"dodekthai", cp_single_1592, 1},
    {"dohiragana", cp_single_1593, 1},
    {"dokatakana", cp_single_1594, 1},
    {"dollar", cp_single_1595, 1},
    {"dollarinferior", cp_single_1596, 1},
    {"dollarmonospace", cp_single_1597, 1},
    {"dollaroldstyle", cp_single_1598, 1},
    {"dollarsmall", cp_single_1599, 1},
    {"dollarsuperior", cp_single_1600, 1},
    {"dong", cp_single_1601, 1},
    {"dorusquare", cp_single_1602, 1},
    {"dotaccent", cp_single_1603, 1},
    {"dotaccentcmb", cp_single_1604, 1},
    {"dotbelowcmb", cp_single_1605, 1},
    {"dotbelowcomb", cp_single_1606, 1},
    {"dotkatakana", cp_single_1607, 1},
    {"dotlessi", cp_single_1608, 1},
    {"dotlessj", cp_single_1609, 1},
    {"dotlessjstrokehook", cp_single_1610, 1},
    {"dotmath", cp_single_1611, 1},
    {"dottedcircle", cp_single_1612, 1},
    {"doubleyodpatah", cp_single_1613, 1},
    {"doubleyodpatahhebrew", cp_single_1614, 1},
    {"downtackbelowcmb", cp_single_1615, 1},
    {"downtackmod", cp_single_1616, 1},
    {"dparen", cp_single_1617, 1},
    {"dsuperior", cp_single_1618, 1},
    {"dtail", cp_single_1619, 1},
    {"dtopbar", cp_single_1620, 1},
    {"duhiragana", cp_single_1621, 1},
    {"dukatakana", cp_single_1622, 1},
    {"dz", cp_single_1623, 1},
    {"dzaltone", cp_single_1624, 1},
    {"dzcaron", cp_single_1625, 1},
    {"dzcurl", cp_single_1626, 1},
    {"dzeabkhasiancyrillic", cp_single_1627, 1},
    {"dzecyrillic", cp_single_1628, 1},
    {"dzhecyrillic", cp_single_1629, 1},
    {"e", cp_single_1630, 1},
    {"eacute", cp_single_1631, 1},
    {"earth", cp_single_1632, 1},
    {"ebengali", cp_single_1633, 1},
    {"ebopomofo", cp_single_1634, 1},
    {"ebreve", cp_single_1635, 1},
    {"ecandradeva", cp_single_1636, 1},
    {"ecandragujarati", cp_single_1637, 1},
    {"ecandravowelsigndeva", cp_single_1638, 1},
    {"ecandravowelsigngujarati", cp_single_1639, 1},
    {"ecaron", cp_single_1640, 1},
    {"ecedillabreve", cp_single_1641, 1},
    {"echarmenian", cp_single_1642, 1},
    {"echyiwnarmenian", cp_single_1643, 1},
    {"ecircle", cp_single_1644, 1},
    {"ecircumflex", cp_single_1645, 1},
    {"ecircumflexacute", cp_single_1646, 1},
    {"ecircumflexbelow", cp_single_1647, 1},
    {"ecircumflexdotbelow", cp_single_1648, 1},
    {"ecircumflexgrave", cp_single_1649, 1},
    {"ecircumflexhookabove", cp_single_1650, 1},
    {"ecircumflextilde", cp_single_1651, 1},
    {"ecyrillic", cp_single_1652, 1},
    {"edblgrave", cp_single_1653, 1},
    {"edeva", cp_single_1654, 1},
    {"edieresis", cp_single_1655, 1},
    {"edot", cp_single_1656, 1},
    {"edotaccent", cp_single_1657, 1},
    {"edotbelow", cp_single_1658, 1},
    {"eegurmukhi", cp_single_1659, 1},
    {"eematragurmukhi", cp_single_1660, 1},
    {"efcyrillic", cp_single_1661, 1},
    {"egrave", cp_single_1662, 1},
    {"egujarati", cp_single_1663, 1},
    {"eharmenian", cp_single_1664, 1},
    {"ehbopomofo", cp_single_1665, 1},
    {"ehiragana", cp_single_1666, 1},
    {"ehookabove", cp_single_1667, 1},
    {"eibopomofo", cp_single_1668, 1},
    {"eight", cp_single_1669, 1},
    {"eightarabic", cp_single_1670, 1},
    {"eightbengali", cp_single_1671, 1},
    {"eightcircle", cp_single_1672, 1},
    {"eightcircleinversesansserif", cp_single_1673, 1},
    {"eightdeva", cp_single_1674, 1},
    {"eighteencircle", cp_single_1675, 1},
    {"eighteenparen", cp_single_1676, 1},
    {"eighteenperiod", cp_single_1677, 1},
    {"eightgujarati", cp_single_1678, 1},
    {"eightgurmukhi", cp_single_1679, 1},
    {"eighthackarabic", cp_single_1680, 1},
    {"eighthangzhou", cp_single_1681, 1},
    {"eighthnotebeamed", cp_single_1682, 1},
    {"eightideographicparen", cp_single_1683, 1},
    {"eightinferior", cp_single_1684, 1},
    {"eightmonospace", cp_single_1685, 1},
    {"eightoldstyle", cp_single_1686, 1},
    {"eightparen", cp_single_1687, 1},
    {"eightperiod", cp_single_1688, 1},
    {"eightpersian", cp_single_1689, 1},
    {"eightroman", cp_single_1690, 1},
    {"eightsuperior", cp_single_1691, 1},
    {"eightthai", cp_single_1692, 1},
    {"einvertedbreve", cp_single_1693, 1},
    {"eiotifiedcyrillic", cp_single_1694, 1},
    {"ekatakana", cp_single_1695, 1},
    {"ekatakanahalfwidth", cp_single_1696, 1},
    {"ekonkargurmukhi", cp_single_1697, 1},
    {"ekorean", cp_single_1698, 1},
    {"elcyrillic", cp_single_1699, 1},
    {"element", cp_single_1700, 1},
    {"elevencircle", cp_single_1701, 1},
    {"elevenparen", cp_single_1702, 1},
    {"elevenperiod", cp_single_1703, 1},
    {"elevenroman", cp_single_1704, 1},
    {"ellipsis", cp_single_1705, 1},
    {"ellipsisvertical", cp_single_1706, 1},
    {"emacron", cp_single_1707, 1},
    {"emacronacute", cp_single_1708, 1},
    {"emacrongrave", cp_single_1709, 1},
    {"emcyrillic", cp_single_1710, 1},
    {"emdash", cp_single_1711, 1},
    {"emdashvertical", cp_single_1712, 1},
    {"emonospace", cp_single_1713, 1},
    {"emphasismarkarmenian", cp_single_1714, 1},
    {"emptyset", cp_single_1715, 1},
    {"enbopomofo", cp_single_1716, 1},
    {"encyrillic", cp_single_1717, 1},
    {"endash", cp_single_1718, 1},
    {"endashvertical", cp_single_1719, 1},
    {"endescendercyrillic", cp_single_1720, 1},
    {"eng", cp_single_1721, 1},
    {"engbopomofo", cp_single_1722, 1},
    {"enghecyrillic", cp_single_1723, 1},
    {"enhookcyrillic", cp_single_1724, 1},
    {"enspace", cp_single_1725, 1},
    {"eogonek", cp_single_1726, 1},
    {"eokorean", cp_single_1727, 1},
    {"eopen", cp_single_1728, 1},
    {"eopenclosed", cp_single_1729, 1},
    {"eopenreversed", cp_single_1730, 1},
    {"eopenreversedclosed", cp_single_1731, 1},
    {"eopenreversedhook", cp_single_1732, 1},
    {"eparen", cp_single_1733, 1},
    {"epsilon", cp_single_1734, 1},
    {"epsilontonos", cp_single_1735, 1},
    {"equal", cp_single_1736, 1},
    {"equalmonospace", cp_single_1737, 1},
    {"equalsmall", cp_single_1738, 1},
    {"equalsuperior", cp_single_1739, 1},
    {"equivalence", cp_single_1740, 1},
    {"erbopomofo", cp_single_1741, 1},
    {"ercyrillic", cp_single_1742, 1},
    {"ereversed", cp_single_1743, 1},
    {"ereversedcyrillic", cp_single_1744, 1},
    {"escyrillic", cp_single_1745, 1},
    {"esdescendercyrillic", cp_single_1746, 1},
    {"esh", cp_single_1747, 1},
    {"eshcurl", cp_single_1748, 1},
    {"eshortdeva", cp_single_1749, 1},
    {"eshortvowelsigndeva", cp_single_1750, 1},
    {"eshreversedloop", cp_single_1751, 1},
    {"eshsquatreversed", cp_single_1752, 1},
    {"esmallhiragana", cp_single_1753, 1},
    {"esmallkatakana", cp_single_1754, 1},
    {"esmallkatakanahalfwidth", cp_single_1755, 1},
    {"estimated", cp_single_1756, 1},
    {"esuperior", cp_single_1757, 1},
    {"eta", cp_single_1758, 1},
    {"etarmenian", cp_single_1759, 1},
    {"etatonos", cp_single_1760, 1},
    {"eth", cp_single_1761, 1},
    {"etilde", cp_single_1762, 1},
    {"etildebelow", cp_single_1763, 1},
    {"etnahtafoukhhebrew", cp_single_1764, 1},
    {"etnahtafoukhlefthebrew", cp_single_1765, 1},
    {"etnahtahebrew", cp_single_1766, 1},
    {"etnahtalefthebrew", cp_single_1767, 1},
    {"eturned", cp_single_1768, 1},
    {"eukorean", cp_single_1769, 1},
    {"euro", cp_single_1770, 1},
    {"evowelsignbengali", cp_single_1771, 1},
    {"evowelsigndeva", cp_single_1772, 1},
    {"evowelsigngujarati", cp_single_1773, 1},
    {"exclam", cp_single_1774, 1},
    {"exclamarmenian", cp_single_1775, 1},
    {"exclamdbl", cp_single_1776, 1},
    {"exclamdown", cp_single_1777, 1},
    {"exclamdownsmall", cp_single_1778, 1},
    {"exclammonospace", cp_single_1779, 1},
    {"exclamsmall", cp_single_1780, 1},
    {"existential", cp_single_1781, 1},
    {"ezh", cp_single_1782, 1},
    {"ezhcaron", cp_single_1783, 1},
    {"ezhcurl", cp_single_1784, 1},
    {"ezhreversed", cp_single_1785, 1},
    {"ezhtail", cp_single_1786, 1},
    {"f", cp_single_1787, 1},
    {"fadeva", cp_single_1788, 1},
    {"fagurmukhi", cp_single_1789, 1},
    {"fahrenheit", cp_single_1790, 1},
    {"fathaarabic", cp_single_1791, 1},
    {"fathalowarabic", cp_single_1792, 1},
    {"fathatanarabic", cp_single_1793, 1},
    {"fbopomofo", cp_single_1794, 1},
    {"fcircle", cp_single_1795, 1},
    {"fdotaccent", cp_single_1796, 1},
    {"feharabic", cp_single_1797, 1},
    {"feharmenian", cp_single_1798, 1},
    {"fehfinalarabic", cp_single_1799, 1},
    {"fehinitialarabic", cp_single_1800, 1},
    {"fehmedialarabic", cp_single_1801, 1},
    {"feicoptic", cp_single_1802, 1},
    {"female", cp_single_1803, 1},
    {"ff", cp_single_1804, 1},
    {"ffi", cp_single_1805, 1},
    {"ffl", cp_single_1806, 1},
    {"fi", cp_single_1807, 1},
    {"fifteencircle", cp_single_1808, 1},
    {"fifteenparen", cp_single_1809, 1},
    {"fifteenperiod", cp_single_1810, 1},
    {"figuredash", cp_single_1811, 1},
    {"filledbox", cp_single_1812, 1},
    {"filledrect", cp_single_1813, 1},
    {"finalkaf", cp_single_1814, 1},
    {"finalkafdagesh", cp_single_1815, 1},
    {"finalkafdageshhebrew", cp_single_1816, 1},
    {"finalkafhebrew", cp_single_1817, 1},
    {"finalkafqamats", cp_1838, 2},
    {"finalkafqamatshebrew", cp_1839, 2},
    {"finalkafsheva", cp_1840, 2},
    {"finalkafshevahebrew", cp_1841, 2},
    {"finalmem", cp_single_1818, 1},
    {"finalmemhebrew", cp_single_1819, 1},
    {"finalnun", cp_single_1820, 1},
    {"finalnunhebrew", cp_single_1821, 1},
    {"finalpe", cp_single_1822, 1},
    {"finalpehebrew", cp_single_1823, 1},
    {"finaltsadi", cp_single_1824, 1},
    {"finaltsadihebrew", cp_single_1825, 1},
    {"firsttonechinese", cp_single_1826, 1},
    {"fisheye", cp_single_1827, 1},
    {"fitacyrillic", cp_single_1828, 1},
    {"five", cp_single_1829, 1},
    {"fivearabic", cp_single_1830, 1},
    {"fivebengali", cp_single_1831, 1},
    {"fivecircle", cp_single_1832, 1},
    {"fivecircleinversesansserif", cp_single_1833, 1},
    {"fivedeva", cp_single_1834, 1},
    {"fiveeighths", cp_single_1835, 1},
    {"fivegujarati", cp_single_1836, 1},
    {"fivegurmukhi", cp_single_1837, 1},
    {"fivehackarabic", cp_single_1838, 1},
    {"fivehangzhou", cp_single_1839, 1},
    {"fiveideographicparen", cp_single_1840, 1},
    {"fiveinferior", cp_single_1841, 1},
    {"fivemonospace", cp_single_1842, 1},
    {"fiveoldstyle", cp_single_1843, 1},
    {"fiveparen", cp_single_1844, 1},
    {"fiveperiod", cp_single_1845, 1},
    {"fivepersian", cp_single_1846, 1},
    {"fiveroman", cp_single_1847, 1},
    {"fivesuperior", cp_single_1848, 1},
    {"fivethai", cp_single_1849, 1},
    {"fl", cp_single_1850, 1},
    {"florin", cp_single_1851, 1},
    {"fmonospace", cp_single_1852, 1},
    {"fmsquare", cp_single_1853, 1},
    {"fofanthai", cp_single_1854, 1},
    {"fofathai", cp_single_1855, 1},
    {"fongmanthai", cp_single_1856, 1},
    {"forall", cp_single_1857, 1},
    {"four", cp_single_1858, 1},
    {"fourarabic", cp_single_1859, 1},
    {"fourbengali", cp_single_1860, 1},
    {"fourcircle", cp_single_1861, 1},
    {"fourcircleinversesansserif", cp_single_1862, 1},
    {"fourdeva", cp_single_1863, 1},
    {"fourgujarati", cp_single_1864, 1},
    {"fourgurmukhi", cp_single_1865, 1},
    {"fourhackarabic", cp_single_1866, 1},
    {"fourhangzhou", cp_single_1867, 1},
    {"fourideographicparen", cp_single_1868, 1},
    {"fourinferior", cp_single_1869, 1},
    {"fourmonospace", cp_single_1870, 1},
    {"fournumeratorbengali", cp_single_1871, 1},
    {"fouroldstyle", cp_single_1872, 1},
    {"fourparen", cp_single_1873, 1},
    {"fourperiod", cp_single_1874, 1},
    {"fourpersian", cp_single_1875, 1},
    {"fourroman", cp_single_1876, 1},
    {"foursuperior", cp_single_1877, 1},
    {"fourteencircle", cp_single_1878, 1},
    {"fourteenparen", cp_single_1879, 1},
    {"fourteenperiod", cp_single_1880, 1},
    {"fourthai", cp_single_1881, 1},
    {"fourthtonechinese", cp_single_1882, 1},
    {"fparen", cp_single_1883, 1},
    {"fraction", cp_single_1884, 1},
    {"franc", cp_single_1885, 1},
    {"g", cp_single_1886, 1},
    {"gabengali", cp_single_1887, 1},
    {"gacute", cp_single_1888, 1},
    {"gadeva", cp_single_1889, 1},
    {"gafarabic", cp_single_1890, 1},
    {"gaffinalarabic", cp_single_1891, 1},
    {"gafinitialarabic", cp_single_1892, 1},
    {"gafmedialarabic", cp_single_1893, 1},
    {"gagujarati", cp_single_1894, 1},
    {"gagurmukhi", cp_single_1895, 1},
    {"gahiragana", cp_single_1896, 1},
    {"gakatakana", cp_single_1897, 1},
    {"gamma", cp_single_1898, 1},
    {"gammalatinsmall", cp_single_1899, 1},
    {"gammasuperior", cp_single_1900, 1},
    {"gangiacoptic", cp_single_1901, 1},
    {"gbopomofo", cp_single_1902, 1},
    {"gbreve", cp_single_1903, 1},
    {"gcaron", cp_single_1904, 1},
    {"gcedilla", cp_single_1905, 1},
    {"gcircle", cp_single_1906, 1},
    {"gcircumflex", cp_single_1907, 1},
    {"gcommaaccent", cp_single_1908, 1},
    {"gdot", cp_single_1909, 1},
    {"gdotaccent", cp_single_1910, 1},
    {"gecyrillic", cp_single_1911, 1},
    {"gehiragana", cp_single_1912, 1},
    {"gekatakana", cp_single_1913, 1},
    {"geometricallyequal", cp_single_1914, 1},
    {"gereshaccenthebrew", cp_single_1915, 1},
    {"gereshhebrew", cp_single_1916, 1},
    {"gereshmuqdamhebrew", cp_single_1917, 1},
    {"germandbls", cp_single_1918, 1},
    {"gershayimaccenthebrew", cp_single_1919, 1},
    {"gershayimhebrew", cp_single_1920, 1},
    {"getamark", cp_single_1921, 1},
    {"ghabengali", cp_single_1922, 1},
    {"ghadarmenian", cp_single_1923, 1},
    {"ghadeva", cp_single_1924, 1},
    {"ghagujarati", cp_single_1925, 1},
    {"ghagurmukhi", cp_single_1926, 1},
    {"ghainarabic", cp_single_1927, 1},
    {"ghainfinalarabic", cp_single_1928, 1},
    {"ghaininitialarabic", cp_single_1929, 1},
    {"ghainmedialarabic", cp_single_1930, 1},
    {"ghemiddlehookcyrillic", cp_single_1931, 1},
    {"ghestrokecyrillic", cp_single_1932, 1},
    {"gheupturncyrillic", cp_single_1933, 1},
    {"ghhadeva", cp_single_1934, 1},
    {"ghhagurmukhi", cp_single_1935, 1},
    {"ghook", cp_single_1936, 1},
    {"ghzsquare", cp_single_1937, 1},
    {"gihiragana", cp_single_1938, 1},
    {"gikatakana", cp_single_1939, 1},
    {"gimarmenian", cp_single_1940, 1},
    {"gimel", cp_single_1941, 1},
    {"gimeldagesh", cp_single_1942, 1},
    {"gimeldageshhebrew", cp_single_1943, 1},
    {"gimelhebrew", cp_single_1944, 1},
    {"gjecyrillic", cp_single_1945, 1},
    {"glottalinvertedstroke", cp_single_1946, 1},
    {"glottalstop", cp_single_1947, 1},
    {"glottalstopinverted", cp_single_1948, 1},
    {"glottalstopmod", cp_single_1949, 1},
    {"glottalstopreversed", cp_single_1950, 1},
    {"glottalstopreversedmod", cp_single_1951, 1},
    {"glottalstopreversedsuperior", cp_single_1952, 1},
    {"glottalstopstroke", cp_single_1953, 1},
    {"glottalstopstrokereversed", cp_single_1954, 1},
    {"gmacron", cp_single_1955, 1},
    {"gmonospace", cp_single_1956, 1},
    {"gohiragana", cp_single_1957, 1},
    {"gokatakana", cp_single_1958, 1},
    {"gparen", cp_single_1959, 1},
    {"gpasquare", cp_single_1960, 1},
    {"gradient", cp_single_1961, 1},
    {"grave", cp_single_1962, 1},
    {"gravebelowcmb", cp_single_1963, 1},
    {"gravecmb", cp_single_1964, 1},
    {"gravecomb", cp_single_1965, 1},
    {"gravedeva", cp_single_1966, 1},
    {"gravelowmod", cp_single_1967, 1},
    {"gravemonospace", cp_single_1968, 1},
    {"gravetonecmb", cp_single_1969, 1},
    {"greater", cp_single_1970, 1},
    {"greaterequal", cp_single_1971, 1},
    {"greaterequalorless", cp_single_1972, 1},
    {"greatermonospace", cp_single_1973, 1},
    {"greaterorequivalent", cp_single_1974, 1},
    {"greaterorless", cp_single_1975, 1},
    {"greateroverequal", cp_single_1976, 1},
    {"greatersmall", cp_single_1977, 1},
    {"gscript", cp_single_1978, 1},
    {"gstroke", cp_single_1979, 1},
    {"guhiragana", cp_single_1980, 1},
    {"guillemotleft", cp_single_1981, 1},
    {"guillemotright", cp_single_1982, 1},
    {"guilsinglleft", cp_single_1983, 1},
    {"guilsinglright", cp_single_1984, 1},
    {"gukatakana", cp_single_1985, 1},
    {"guramusquare", cp_single_1986, 1},
    {"gysquare", cp_single_1987, 1},
    {"h", cp_single_1988, 1},
    {"haabkhasiancyrillic", cp_single_1989, 1},
    {"haaltonearabic", cp_single_1990, 1},
    {"habengali", cp_single_1991, 1},
    {"hadescendercyrillic", cp_single_1992, 1},
    {"hadeva", cp_single_1993, 1},
    {"hagujarati", cp_single_1994, 1},
    {"hagurmukhi", cp_single_1995, 1},
    {"haharabic", cp_single_1996, 1},
    {"hahfinalarabic", cp_single_1997, 1},
    {"hahinitialarabic", cp_single_1998, 1},
    {"hahiragana", cp_single_1999, 1},
    {"hahmedialarabic", cp_single_2000, 1},
    {"haitusquare", cp_single_2001, 1},
    {"hakatakana", cp_single_2002, 1},
    {"hakatakanahalfwidth", cp_single_2003, 1},
    {"halantgurmukhi", cp_single_2004, 1},
    {"hamzaarabic", cp_single_2005, 1},
    {"hamzadammaarabic", cp_2030, 2},
    {"hamzadammatanarabic", cp_2031, 2},
    {"hamzafathaarabic", cp_2032, 2},
    {"hamzafathatanarabic", cp_2033, 2},
    {"hamzalowarabic", cp_single_2006, 1},
    {"hamzalowkasraarabic", cp_2035, 2},
    {"hamzalowkasratanarabic", cp_2036, 2},
    {"hamzasukunarabic", cp_2037, 2},
    {"hangulfiller", cp_single_2007, 1},
    {"hardsigncyrillic", cp_single_2008, 1},
    {"harpoonleftbarbup", cp_single_2009, 1},
    {"harpoonrightbarbup", cp_single_2010, 1},
    {"hasquare", cp_single_2011, 1},
    {"hatafpatah", cp_single_2012, 1},
    {"hatafpatah16", cp_single_2013, 1},
    {"hatafpatah23", cp_single_2014, 1},
    {"hatafpatah2f", cp_single_2015, 1},
    {"hatafpatahhebrew", cp_single_2016, 1},
    {"hatafpatahnarrowhebrew", cp_single_2017, 1},
    {"hatafpatahquarterhebrew", cp_single_2018, 1},
    {"hatafpatahwidehebrew", cp_single_2019, 1},
    {"hatafqamats", cp_single_2020, 1},
    {"hatafqamats1b", cp_single_2021, 1},
    {"hatafqamats28", cp_single_2022, 1},
    {"hatafqamats34", cp_single_2023, 1},
    {"hatafqamatshebrew", cp_single_2024, 1},
    {"hatafqamatsnarrowhebrew", cp_single_2025, 1},
    {"hatafqamatsquarterhebrew", cp_single_2026, 1},
    {"hatafqamatswidehebrew", cp_single_2027, 1},
    {"hatafsegol", cp_single_2028, 1},
    {"hatafsegol17", cp_single_2029, 1},
    {"hatafsegol24", cp_single_2030, 1},
    {"hatafsegol30", cp_single_2031, 1},
    {"hatafsegolhebrew", cp_single_2032, 1},
    {"hatafsegolnarrowhebrew", cp_single_2033, 1},
    {"hatafsegolquarterhebrew", cp_single_2034, 1},
    {"hatafsegolwidehebrew", cp_single_2035, 1},
    {"hbar", cp_single_2036, 1},
    {"hbopomofo", cp_single_2037, 1},
    {"hbrevebelow", cp_single_2038, 1},
    {"hcedilla", cp_single_2039, 1},
    {"hcircle", cp_single_2040, 1},
    {"hcircumflex", cp_single_2041, 1},
    {"hdieresis", cp_single_2042, 1},
    {"hdotaccent", cp_single_2043, 1},
    {"hdotbelow", cp_single_2044, 1},
    {"he", cp_single_2045, 1},
    {"heart", cp_single_2046, 1},
    {"heartsuitblack", cp_single_2047, 1},
    {"heartsuitwhite", cp_single_2048, 1},
    {"hedagesh", cp_single_2049, 1},
    {"hedageshhebrew", cp_single_2050, 1},
    {"hehaltonearabic", cp_single_2051, 1},
    {"heharabic", cp_single_2052, 1},
    {"hehebrew", cp_single_2053, 1},
    {"hehfinalaltonearabic", cp_single_2054, 1},
    {"hehfinalalttwoarabic", cp_single_2055, 1},
    {"hehfinalarabic", cp_single_2056, 1},
    {"hehhamzaabovefinalarabic", cp_single_2057, 1},
    {"hehhamzaaboveisolatedarabic", cp_single_2058, 1},
    {"hehinitialaltonearabic", cp_single_2059, 1},
    {"hehinitialarabic", cp_single_2060, 1},
    {"hehiragana", cp_single_2061, 1},
    {"hehmedialaltonearabic", cp_single_2062, 1},
    {"hehmedialarabic", cp_single_2063, 1},
    {"heiseierasquare", cp_single_2064, 1},
    {"hekatakana", cp_single_2065, 1},
    {"hekatakanahalfwidth", cp_single_2066, 1},
    {"hekutaarusquare", cp_single_2067, 1},
    {"henghook", cp_single_2068, 1},
    {"herutusquare", cp_single_2069, 1},
    {"het", cp_single_2070, 1},
    {"hethebrew", cp_single_2071, 1},
    {"hhook", cp_single_2072, 1},
    {"hhooksuperior", cp_single_2073, 1},
    {"hieuhacirclekorean", cp_single_2074, 1},
    {"hieuhaparenkorean", cp_single_2075, 1},
    {"hieuhcirclekorean", cp_single_2076, 1},
    {"hieuhkorean", cp_single_2077, 1},
    {"hieuhparenkorean", cp_single_2078, 1},
    {"hihiragana", cp_single_2079, 1},
    {"hikatakana", cp_single_2080, 1},
    {"hikatakanahalfwidth", cp_single_2081, 1},
    {"hiriq", cp_single_2082, 1},
    {"hiriq14", cp_single_2083, 1},
    {"hiriq21", cp_single_2084, 1},
    {"hiriq2d", cp_single_2085, 1},
    {"hiriqhebrew", cp_single_2086, 1},
    {"hiriqnarrowhebrew", cp_single_2087, 1},
    {"hiriqquarterhebrew", cp_single_2088, 1},
    {"hiriqwidehebrew", cp_single_2089, 1},
    {"hlinebelow", cp_single_2090, 1},
    {"hmonospace", cp_single_2091, 1},
    {"hoarmenian", cp_single_2092, 1},
    {"hohipthai", cp_single_2093, 1},
    {"hohiragana", cp_single_2094, 1},
    {"hokatakana", cp_single_2095, 1},
    {"hokatakanahalfwidth", cp_single_2096, 1},
    {"holam", cp_single_2097, 1},
    {"holam19", cp_single_2098, 1},
    {"holam26", cp_single_2099, 1},
    {"holam32", cp_single_2100, 1},
    {"holamhebrew", cp_single_2101, 1},
    {"holamnarrowhebrew", cp_single_2102, 1},
    {"holamquarterhebrew", cp_single_2103, 1},
    {"holamwidehebrew", cp_single_2104, 1},
    {"honokhukthai", cp_single_2105, 1},
    {"hookabovecomb", cp_single_2106, 1},
    {"hookcmb", cp_single_2107, 1},
    {"hookpalatalizedbelowcmb", cp_single_2108, 1},
    {"hookretroflexbelowcmb", cp_single_2109, 1},
    {"hoonsquare", cp_single_2110, 1},
    {"horicoptic", cp_single_2111, 1},
    {"horizontalbar", cp_single_2112, 1},
    {"horncmb", cp_single_2113, 1},
    {"hotsprings", cp_single_2114, 1},
    {"house", cp_single_2115, 1},
    {"hparen", cp_single_2116, 1},
    {"hsuperior", cp_single_2117, 1},
    {"hturned", cp_single_2118, 1},
    {"huhiragana", cp_single_2119, 1},
    {"huiitosquare", cp_single_2120, 1},
    {"hukatakana", cp_single_2121, 1},
    {"hukatakanahalfwidth", cp_single_2122, 1},
    {"hungarumlaut", cp_single_2123, 1},
    {"hungarumlautcmb", cp_single_2124, 1},
    {"hv", cp_single_2125, 1},
    {"hyphen", cp_single_2126, 1},
    {"hypheninferior", cp_single_2127, 1},
    {"hyphenmonospace", cp_single_2128, 1},
    {"hyphensmall", cp_single_2129, 1},
    {"hyphensuperior", cp_single_2130, 1},
    {"hyphentwo", cp_single_2131, 1},
    {"i", cp_single_2132, 1},
    {"iacute", cp_single_2133, 1},
    {"iacyrillic", cp_single_2134, 1},
    {"ibengali", cp_single_2135, 1},
    {"ibopomofo", cp_single_2136, 1},
    {"ibreve", cp_single_2137, 1},
    {"icaron", cp_single_2138, 1},
    {"icircle", cp_single_2139, 1},
    {"icircumflex", cp_single_2140, 1},
    {"icyrillic", cp_single_2141, 1},
    {"idblgrave", cp_single_2142, 1},
    {"ideographearthcircle", cp_single_2143, 1},
    {"ideographfirecircle", cp_single_2144, 1},
    {"ideographicallianceparen", cp_single_2145, 1},
    {"ideographiccallparen", cp_single_2146, 1},
    {"ideographiccentrecircle", cp_single_2147, 1},
    {"ideographicclose", cp_single_2148, 1},
    {"ideographiccomma", cp_single_2149, 1},
    {"ideographiccommaleft", cp_single_2150, 1},
    {"ideographiccongratulationparen", cp_single_2151, 1},
    {"ideographiccorrectcircle", cp_single_2152, 1},
    {"ideographicearthparen", cp_single_2153, 1},
    {"ideographicenterpriseparen", cp_single_2154, 1},
    {"ideographicexcellentcircle", cp_single_2155, 1},
    {"ideographicfestivalparen", cp_single_2156, 1},
    {"ideographicfinancialcircle", cp_single_2157, 1},
    {"ideographicfinancialparen", cp_single_2158, 1},
    {"ideographicfireparen", cp_single_2159, 1},
    {"ideographichaveparen", cp_single_2160, 1},
    {"ideographichighcircle", cp_single_2161, 1},
    {"ideographiciterationmark", cp_single_2162, 1},
    {"ideographiclaborcircle", cp_single_2163, 1},
    {"ideographiclaborparen", cp_single_2164, 1},
    {"ideographicleftcircle", cp_single_2165, 1},
    {"ideographiclowcircle", cp_single_2166, 1},
    {"ideographicmedicinecircle", cp_single_2167, 1},
    {"ideographicmetalparen", cp_single_2168, 1},
    {"ideographicmoonparen", cp_single_2169, 1},
    {"ideographicnameparen", cp_single_2170, 1},
    {"ideographicperiod", cp_single_2171, 1},
    {"ideographicprintcircle", cp_single_2172, 1},
    {"ideographicreachparen", cp_single_2173, 1},
    {"ideographicrepresentparen", cp_single_2174, 1},
    {"ideographicresourceparen", cp_single_2175, 1},
    {"ideographicrightcircle", cp_single_2176, 1},
    {"ideographicsecretcircle", cp_single_2177, 1},
    {"ideographicselfparen", cp_single_2178, 1},
    {"ideographicsocietyparen", cp_single_2179, 1},
    {"ideographicspace", cp_single_2180, 1},
    {"ideographicspecialparen", cp_single_2181, 1},
    {"ideographicstockparen", cp_single_2182, 1},
    {"ideographicstudyparen", cp_single_2183, 1},
    {"ideographicsunparen", cp_single_2184, 1},
    {"ideographicsuperviseparen", cp_single_2185, 1},
    {"ideographicwaterparen", cp_single_2186, 1},
    {"ideographicwoodparen", cp_single_2187, 1},
    {"ideographiczero", cp_single_2188, 1},
    {"ideographmetalcircle", cp_single_2189, 1},
    {"ideographmooncircle", cp_single_2190, 1},
    {"ideographnamecircle", cp_single_2191, 1},
    {"ideographsuncircle", cp_single_2192, 1},
    {"ideographwatercircle", cp_single_2193, 1},
    {"ideographwoodcircle", cp_single_2194, 1},
    {"ideva", cp_single_2195, 1},
    {"idieresis", cp_single_2196, 1},
    {"idieresisacute", cp_single_2197, 1},
    {"idieresiscyrillic", cp_single_2198, 1},
    {"idotbelow", cp_single_2199, 1},
    {"iebrevecyrillic", cp_single_2200, 1},
    {"iecyrillic", cp_single_2201, 1},
    {"ieungacirclekorean", cp_single_2202, 1},
    {"ieungaparenkorean", cp_single_2203, 1},
    {"ieungcirclekorean", cp_single_2204, 1},
    {"ieungkorean", cp_single_2205, 1},
    {"ieungparenkorean", cp_single_2206, 1},
    {"igrave", cp_single_2207, 1},
    {"igujarati", cp_single_2208, 1},
    {"igurmukhi", cp_single_2209, 1},
    {"ihiragana", cp_single_2210, 1},
    {"ihookabove", cp_single_2211, 1},
    {"iibengali", cp_single_2212, 1},
    {"iicyrillic", cp_single_2213, 1},
    {"iideva", cp_single_2214, 1},
    {"iigujarati", cp_single_2215, 1},
    {"iigurmukhi", cp_single_2216, 1},
    {"iimatragurmukhi", cp_single_2217, 1},
    {"iinvertedbreve", cp_single_2218, 1},
    {"iishortcyrillic", cp_single_2219, 1},
    {"iivowelsignbengali", cp_single_2220, 1},
    {"iivowelsigndeva", cp_single_2221, 1},
    {"iivowelsigngujarati", cp_single_2222, 1},
    {"ij", cp_single_2223, 1},
    {"ikatakana", cp_single_2224, 1},
    {"ikatakanahalfwidth", cp_single_2225, 1},
    {"ikorean", cp_single_2226, 1},
    {"ilde", cp_single_2227, 1},
    {"iluyhebrew", cp_single_2228, 1},
    {"imacron", cp_single_2229, 1},
    {"imacroncyrillic", cp_single_2230, 1},
    {"imageorapproximatelyequal", cp_single_2231, 1},
    {"imatragurmukhi", cp_single_2232, 1},
    {"imonospace", cp_single_2233, 1},
    {"increment", cp_single_2234, 1},
    {"infinity", cp_single_2235, 1},
    {"iniarmenian", cp_single_2236, 1},
    {"integral", cp_single_2237, 1},
    {"integralbottom", cp_single_2238, 1},
    {"integralbt", cp_single_2239, 1},
    {"integralex", cp_single_2240, 1},
    {"integraltop", cp_single_2241, 1},
    {"integraltp", cp_single_2242, 1},
    {"intersection", cp_single_2243, 1},
    {"intisquare", cp_single_2244, 1},
    {"invbullet", cp_single_2245, 1},
    {"invcircle", cp_single_2246, 1},
    {"invsmileface", cp_single_2247, 1},
    {"iocyrillic", cp_single_2248, 1},
    {"iogonek", cp_single_2249, 1},
    {"iota", cp_single_2250, 1},
    {"iotadieresis", cp_single_2251, 1},
    {"iotadieresistonos", cp_single_2252, 1},
    {"iotalatin", cp_single_2253, 1},
    {"iotatonos", cp_single_2254, 1},
    {"iparen", cp_single_2255, 1},
    {"irigurmukhi", cp_single_2256, 1},
    {"ismallhiragana", cp_single_2257, 1},
    {"ismallkatakana", cp_single_2258, 1},
    {"ismallkatakanahalfwidth", cp_single_2259, 1},
    {"issharbengali", cp_single_2260, 1},
    {"istroke", cp_single_2261, 1},
    {"isuperior", cp_single_2262, 1},
    {"iterationhiragana", cp_single_2263, 1},
    {"iterationkatakana", cp_single_2264, 1},
    {"itilde", cp_single_2265, 1},
    {"itildebelow", cp_single_2266, 1},
    {"iubopomofo", cp_single_2267, 1},
    {"iucyrillic", cp_single_2268, 1},
    {"ivowelsignbengali", cp_single_2269, 1},
    {"ivowelsigndeva", cp_single_2270, 1},
    {"ivowelsigngujarati", cp_single_2271, 1},
    {"izhitsacyrillic", cp_single_2272, 1},
    {"izhitsadblgravecyrillic", cp_single_2273, 1},
    {"j", cp_single_2274, 1},
    {"jaarmenian", cp_single_2275, 1},
    {"jabengali", cp_single_2276, 1},
    {"jadeva", cp_single_2277, 1},
    {"jagujarati", cp_single_2278, 1},
    {"jagurmukhi", cp_single_2279, 1},
    {"jbopomofo", cp_single_2280, 1},
    {"jcaron", cp_single_2281, 1},
    {"jcircle", cp_single_2282, 1},
    {"jcircumflex", cp_single_2283, 1},
    {"jcrossedtail", cp_single_2284, 1},
    {"jdotlessstroke", cp_single_2285, 1},
    {"jecyrillic", cp_single_2286, 1},
    {"jeemarabic", cp_single_2287, 1},
    {"jeemfinalarabic", cp_single_2288, 1},
    {"jeeminitialarabic", cp_single_2289, 1},
    {"jeemmedialarabic", cp_single_2290, 1},
    {"jeharabic", cp_single_2291, 1},
    {"jehfinalarabic", cp_single_2292, 1},
    {"jhabengali", cp_single_2293, 1},
    {"jhadeva", cp_single_2294, 1},
    {"jhagujarati", cp_single_2295, 1},
    {"jhagurmukhi", cp_single_2296, 1},
    {"jheharmenian", cp_single_2297, 1},
    {"jis", cp_single_2298, 1},
    {"jmonospace", cp_single_2299, 1},
    {"jparen", cp_single_2300, 1},
    {"jsuperior", cp_single_2301, 1},
    {"k", cp_single_2302, 1},
    {"kabashkircyrillic", cp_single_2303, 1},
    {"kabengali", cp_single_2304, 1},
    {"kacute", cp_single_2305, 1},
    {"kacyrillic", cp_single_2306, 1},
    {"kadescendercyrillic", cp_single_2307, 1},
    {"kadeva", cp_single_2308, 1},
    {"kaf", cp_single_2309, 1},
    {"kafarabic", cp_single_2310, 1},
    {"kafdagesh", cp_single_2311, 1},
    {"kafdageshhebrew", cp_single_2312, 1},
    {"kaffinalarabic", cp_single_2313, 1},
    {"kafhebrew", cp_single_2314, 1},
    {"kafinitialarabic", cp_single_2315, 1},
    {"kafmedialarabic", cp_single_2316, 1},
    {"kafrafehebrew", cp_single_2317, 1},
    {"kagujarati", cp_single_2318, 1},
    {"kagurmukhi", cp_single_2319, 1},
    {"kahiragana", cp_single_2320, 1},
    {"kahookcyrillic", cp_single_2321, 1},
    {"kakatakana", cp_single_2322, 1},
    {"kakatakanahalfwidth", cp_single_2323, 1},
    {"kappa", cp_single_2324, 1},
    {"kappasymbolgreek", cp_single_2325, 1},
    {"kapyeounmieumkorean", cp_single_2326, 1},
    {"kapyeounphieuphkorean", cp_single_2327, 1},
    {"kapyeounpieupkorean", cp_single_2328, 1},
    {"kapyeounssangpieupkorean", cp_single_2329, 1},
    {"karoriisquare", cp_single_2330, 1},
    {"kashidaautoarabic", cp_single_2331, 1},
    {"kashidaautonosidebearingarabic", cp_single_2332, 1},
    {"kasmallkatakana", cp_single_2333, 1},
    {"kasquare", cp_single_2334, 1},
    {"kasraarabic", cp_single_2335, 1},
    {"kasratanarabic", cp_single_2336, 1},
    {"kastrokecyrillic", cp_single_2337, 1},
    {"katahiraprolongmarkhalfwidth", cp_single_2338, 1},
    {"kaverticalstrokecyrillic", cp_single_2339, 1},
    {"kbopomofo", cp_single_2340, 1},
    {"kcalsquare", cp_single_2341, 1},
    {"kcaron", cp_single_2342, 1},
    {"kcedilla", cp_single_2343, 1},
    {"kcircle", cp_single_2344, 1},
    {"kcommaaccent", cp_single_2345, 1},
    {"kdotbelow", cp_single_2346, 1},
    {"keharmenian", cp_single_2347, 1},
    {"kehiragana", cp_single_2348, 1},
    {"kekatakana", cp_single_2349, 1},
    {"kekatakanahalfwidth", cp_single_2350, 1},
    {"kenarmenian", cp_single_2351, 1},
    {"kesmallkatakana", cp_single_2352, 1},
    {"kgreenlandic", cp_single_2353, 1},
    {"khabengali", cp_single_2354, 1},
    {"khacyrillic", cp_single_2355, 1},
    {"khadeva", cp_single_2356, 1},
    {"khagujarati", cp_single_2357, 1},
    {"khagurmukhi", cp_single_2358, 1},
    {"khaharabic", cp_single_2359, 1},
    {"khahfinalarabic", cp_single_2360, 1},
    {"khahinitialarabic", cp_single_2361, 1},
    {"khahmedialarabic", cp_single_2362, 1},
    {"kheicoptic", cp_single_2363, 1},
    {"khhadeva", cp_single_2364, 1},
    {"khhagurmukhi", cp_single_2365, 1},
    {"khieukhacirclekorean", cp_single_2366, 1},
    {"khieukhaparenkorean", cp_single_2367, 1},
    {"khieukhcirclekorean", cp_single_2368, 1},
    {"khieukhkorean", cp_single_2369, 1},
    {"khieukhparenkorean", cp_single_2370, 1},
    {"khokhaithai", cp_single_2371, 1},
    {"khokhonthai", cp_single_2372, 1},
    {"khokhuatthai", cp_single_2373, 1},
    {"khokhwaithai", cp_single_2374, 1},
    {"khomutthai", cp_single_2375, 1},
    {"khook", cp_single_2376, 1},
    {"khorakhangthai", cp_single_2377, 1},
    {"khzsquare", cp_single_2378, 1},
    {"kihiragana", cp_single_2379, 1},
    {"kikatakana", cp_single_2380, 1},
    {"kikatakanahalfwidth", cp_single_2381, 1},
    {"kiroguramusquare", cp_single_2382, 1},
    {"kiromeetorusquare", cp_single_2383, 1},
    {"kirosquare", cp_single_2384, 1},
    {"kiyeokacirclekorean", cp_single_2385, 1},
    {"kiyeokaparenkorean", cp_single_2386, 1},
    {"kiyeokcirclekorean", cp_single_2387, 1},
    {"kiyeokkorean", cp_single_2388, 1},
    {"kiyeokparenkorean", cp_single_2389, 1},
    {"kiyeoksioskorean", cp_single_2390, 1},
    {"kjecyrillic", cp_single_2391, 1},
    {"klinebelow", cp_single_2392, 1},
    {"klsquare", cp_single_2393, 1},
    {"kmcubedsquare", cp_single_2394, 1},
    {"kmonospace", cp_single_2395, 1},
    {"kmsquaredsquare", cp_single_2396, 1},
    {"kohiragana", cp_single_2397, 1},
    {"kohmsquare", cp_single_2398, 1},
    {"kokaithai", cp_single_2399, 1},
    {"kokatakana", cp_single_2400, 1},
    {"kokatakanahalfwidth", cp_single_2401, 1},
    {"kooposquare", cp_single_2402, 1},
    {"koppacyrillic", cp_single_2403, 1},
    {"koreanstandardsymbol", cp_single_2404, 1},
    {"koroniscmb", cp_single_2405, 1},
    {"kparen", cp_single_2406, 1},
    {"kpasquare", cp_single_2407, 1},
    {"ksicyrillic", cp_single_2408, 1},
    {"ktsquare", cp_single_2409, 1},
    {"kturned", cp_single_2410, 1},
    {"kuhiragana", cp_single_2411, 1},
    {"kukatakana", cp_single_2412, 1},
    {"kukatakanahalfwidth", cp_single_2413, 1},
    {"kvsquare", cp_single_2414, 1},
    {"kwsquare", cp_single_2415, 1},
    {"l", cp_single_2416, 1},
    {"labengali", cp_single_2417, 1},
    {"lacute", cp_single_2418, 1},
    {"ladeva", cp_single_2419, 1},
    {"lagujarati", cp_single_2420, 1},
    {"lagurmukhi", cp_single_2421, 1},
    {"lakkhangyaothai", cp_single_2422, 1},
    {"lamaleffinalarabic", cp_single_2423, 1},
    {"lamalefhamzaabovefinalarabic", cp_single_2424, 1},
    {"lamalefhamzaaboveisolatedarabic", cp_single_2425, 1},
    {"lamalefhamzabelowfinalarabic", cp_single_2426, 1},
    {"lamalefhamzabelowisolatedarabic", cp_single_2427, 1},
    {"lamalefisolatedarabic", cp_single_2428, 1},
    {"lamalefmaddaabovefinalarabic", cp_single_2429, 1},
    {"lamalefmaddaaboveisolatedarabic", cp_single_2430, 1},
    {"lamarabic", cp_single_2431, 1},
    {"lambda", cp_single_2432, 1},
    {"lambdastroke", cp_single_2433, 1},
    {"lamed", cp_single_2434, 1},
    {"lameddagesh", cp_single_2435, 1},
    {"lameddageshhebrew", cp_single_2436, 1},
    {"lamedhebrew", cp_single_2437, 1},
    {"lamedholam", cp_2469, 2},
    {"lamedholamdagesh", cp_2470, 3},
    {"lamedholamdageshhebrew", cp_2471, 3},
    {"lamedholamhebrew", cp_2472, 2},
    {"lamfinalarabic", cp_single_2438, 1},
    {"lamhahinitialarabic", cp_single_2439, 1},
    {"laminitialarabic", cp_single_2440, 1},
    {"lamjeeminitialarabic", cp_single_2441, 1},
    {"lamkhahinitialarabic", cp_single_2442, 1},
    {"lamlamhehisolatedarabic", cp_single_2443, 1},
    {"lammedialarabic", cp_single_2444, 1},
    {"lammeemhahinitialarabic", cp_single_2445, 1},
    {"lammeeminitialarabic", cp_single_2446, 1},
    {"lammeemjeeminitialarabic", cp_2482, 3},
    {"lammeemkhahinitialarabic", cp_2483, 3},
    {"largecircle", cp_single_2447, 1},
    {"lbar", cp_single_2448, 1},
    {"lbelt", cp_single_2449, 1},
    {"lbopomofo", cp_single_2450, 1},
    {"lcaron", cp_single_2451, 1},
    {"lcedilla", cp_single_2452, 1},
    {"lcircle", cp_single_2453, 1},
    {"lcircumflexbelow", cp_single_2454, 1},
    {"lcommaaccent", cp_single_2455, 1},
    {"ldot", cp_single_2456, 1},
    {"ldotaccent", cp_single_2457, 1},
    {"ldotbelow", cp_single_2458, 1},
    {"ldotbelowmacron", cp_single_2459, 1},
    {"leftangleabovecmb", cp_single_2460, 1},
    {"lefttackbelowcmb", cp_single_2461, 1},
    {"less", cp_single_2462, 1},
    {"lessequal", cp_single_2463, 1},
    {"lessequalorgreater", cp_single_2464, 1},
    {"lessmonospace", cp_single_2465, 1},
    {"lessorequivalent", cp_single_2466, 1},
    {"lessorgreater", cp_single_2467, 1},
    {"lessoverequal", cp_single_2468, 1},
    {"lesssmall", cp_single_2469, 1},
    {"lezh", cp_single_2470, 1},
    {"lfblock", cp_single_2471, 1},
    {"lhookretroflex", cp_single_2472, 1},
    {"lira", cp_single_2473, 1},
    {"liwnarmenian", cp_single_2474, 1},
    {"lj", cp_single_2475, 1},
    {"ljecyrillic", cp_single_2476, 1},
    {"ll", cp_single_2477, 1},
    {"lladeva", cp_single_2478, 1},
    {"llagujarati", cp_single_2479, 1},
    {"llinebelow", cp_single_2480, 1},
    {"llladeva", cp_single_2481, 1},
    {"llvocalicbengali", cp_single_2482, 1},
    {"llvocalicdeva", cp_single_2483, 1},
    {"llvocalicvowelsignbengali", cp_single_2484, 1},
    {"llvocalicvowelsigndeva", cp_single_2485, 1},
    {"lmiddletilde", cp_single_2486, 1},
    {"lmonospace", cp_single_2487, 1},
    {"lmsquare", cp_single_2488, 1},
    {"lochulathai", cp_single_2489, 1},
    {"logicaland", cp_single_2490, 1},
    {"logicalnot", cp_single_2491, 1},
    {"logicalnotreversed", cp_single_2492, 1},
    {"logicalor", cp_single_2493, 1},
    {"lolingthai", cp_single_2494, 1},
    {"longs", cp_single_2495, 1},
    {"lowlinecenterline", cp_single_2496, 1},
    {"lowlinecmb", cp_single_2497, 1},
    {"lowlinedashed", cp_single_2498, 1},
    {"lozenge", cp_single_2499, 1},
    {"lparen", cp_single_2500, 1},
    {"lslash", cp_single_2501, 1},
    {"lsquare", cp_single_2502, 1},
    {"lsuperior", cp_single_2503, 1},
    {"ltshade", cp_single_2504, 1},
    {"luthai", cp_single_2505, 1},
    {"lvocalicbengali", cp_single_2506, 1},
    {"lvocalicdeva", cp_single_2507, 1},
    {"lvocalicvowelsignbengali", cp_single_2508, 1},
    {"lvocalicvowelsigndeva", cp_single_2509, 1},
    {"lxsquare", cp_single_2510, 1},
    {"m", cp_single_2511, 1},
    {"mabengali", cp_single_2512, 1},
    {"macron", cp_single_2513, 1},
    {"macronbelowcmb", cp_single_2514, 1},
    {"macroncmb", cp_single_2515, 1},
    {"macronlowmod", cp_single_2516, 1},
    {"macronmonospace", cp_single_2517, 1},
    {"macute", cp_single_2518, 1},
    {"madeva", cp_single_2519, 1},
    {"magujarati", cp_single_2520, 1},
    {"magurmukhi", cp_single_2521, 1},
    {"mahapakhhebrew", cp_single_2522, 1},
    {"mahapakhlefthebrew", cp_single_2523, 1},
    {"mahiragana", cp_single_2524, 1},
    {"maichattawalowleftthai", cp_single_2525, 1},
    {"maichattawalowrightthai", cp_single_2526, 1},
    {"maichattawathai", cp_single_2527, 1},
    {"maichattawaupperleftthai", cp_single_2528, 1},
    {"maieklowleftthai", cp_single_2529, 1},
    {"maieklowrightthai", cp_single_2530, 1},
    {"maiekthai", cp_single_2531, 1},
    {"maiekupperleftthai", cp_single_2532, 1},
    {"maihanakatleftthai", cp_single_2533, 1},
    {"maihanakatthai", cp_single_2534, 1},
    {"maitaikhuleftthai", cp_single_2535, 1},
    {"maitaikhuthai", cp_single_2536, 1},
    {"maitholowleftthai", cp_single_2537, 1},
    {"maitholowrightthai", cp_single_2538, 1},
    {"maithothai", cp_single_2539, 1},
    {"maithoupperleftthai", cp_single_2540, 1},
    {"maitrilowleftthai", cp_single_2541, 1},
    {"maitrilowrightthai", cp_single_2542, 1},
    {"maitrithai", cp_single_2543, 1},
    {"maitriupperleftthai", cp_single_2544, 1},
    {"maiyamokthai", cp_single_2545, 1},
    {"makatakana", cp_single_2546, 1},
    {"makatakanahalfwidth", cp_single_2547, 1},
    {"male", cp_single_2548, 1},
    {"mansyonsquare", cp_single_2549, 1},
    {"maqafhebrew", cp_single_2550, 1},
    {"mars", cp_single_2551, 1},
    {"masoracirclehebrew", cp_single_2552, 1},
    {"masquare", cp_single_2553, 1},
    {"mbopomofo", cp_single_2554, 1},
    {"mbsquare", cp_single_2555, 1},
    {"mcircle", cp_single_2556, 1},
    {"mcubedsquare", cp_single_2557, 1},
    {"mdotaccent", cp_single_2558, 1},
    {"mdotbelow", cp_single_2559, 1},
    {"meemarabic", cp_single_2560, 1},
    {"meemfinalarabic", cp_single_2561, 1},
    {"meeminitialarabic", cp_single_2562, 1},
    {"meemmedialarabic", cp_single_2563, 1},
    {"meemmeeminitialarabic", cp_single_2564, 1},
    {"meemmeemisolatedarabic", cp_single_2565, 1},
    {"meetorusquare", cp_single_2566, 1},
    {"mehiragana", cp_single_2567, 1},
    {"meizierasquare", cp_single_2568, 1},
    {"mekatakana", cp_single_2569, 1},
    {"mekatakanahalfwidth", cp_single_2570, 1},
    {"mem", cp_single_2571, 1},
    {"memdagesh", cp_single_2572, 1},
    {"memdageshhebrew", cp_single_2573, 1},
    {"memhebrew", cp_single_2574, 1},
    {"menarmenian", cp_single_2575, 1},
    {"merkhahebrew", cp_single_2576, 1},
    {"merkhakefulahebrew", cp_single_2577, 1},
    {"merkhakefulalefthebrew", cp_single_2578, 1},
    {"merkhalefthebrew", cp_single_2579, 1},
    {"mhook", cp_single_2580, 1},
    {"mhzsquare", cp_single_2581, 1},
    {"middledotkatakanahalfwidth", cp_single_2582, 1},
    {"middot", cp_single_2583, 1},
    {"mieumacirclekorean", cp_single_2584, 1},
    {"mieumaparenkorean", cp_single_2585, 1},
    {"mieumcirclekorean", cp_single_2586, 1},
    {"mieumkorean", cp_single_2587, 1},
    {"mieumpansioskorean", cp_single_2588, 1},
    {"mieumparenkorean", cp_single_2589, 1},
    {"mieumpieupkorean", cp_single_2590, 1},
    {"mieumsioskorean", cp_single_2591, 1},
    {"mihiragana", cp_single_2592, 1},
    {"mikatakana", cp_single_2593, 1},
    {"mikatakanahalfwidth", cp_single_2594, 1},
    {"minus", cp_single_2595, 1},
    {"minusbelowcmb", cp_single_2596, 1},
    {"minuscircle", cp_single_2597, 1},
    {"minusmod", cp_single_2598, 1},
    {"minusplus", cp_single_2599, 1},
    {"minute", cp_single_2600, 1},
    {"miribaarusquare", cp_single_2601, 1},
    {"mirisquare", cp_single_2602, 1},
    {"mlonglegturned", cp_single_2603, 1},
    {"mlsquare", cp_single_2604, 1},
    {"mmcubedsquare", cp_single_2605, 1},
    {"mmonospace", cp_single_2606, 1},
    {"mmsquaredsquare", cp_single_2607, 1},
    {"mohiragana", cp_single_2608, 1},
    {"mohmsquare", cp_single_2609, 1},
    {"mokatakana", cp_single_2610, 1},
    {"mokatakanahalfwidth", cp_single_2611, 1},
    {"molsquare", cp_single_2612, 1},
    {"momathai", cp_single_2613, 1},
    {"moverssquare", cp_single_2614, 1},
    {"moverssquaredsquare", cp_single_2615, 1},
    {"mparen", cp_single_2616, 1},
    {"mpasquare", cp_single_2617, 1},
    {"mssquare", cp_single_2618, 1},
    {"msuperior", cp_single_2619, 1},
    {"mturned", cp_single_2620, 1},
    {"mu", cp_single_2621, 1},
    {"mu1", cp_single_2622, 1},
    {"muasquare", cp_single_2623, 1},
    {"muchgreater", cp_single_2624, 1},
    {"muchless", cp_single_2625, 1},
    {"mufsquare", cp_single_2626, 1},
    {"mugreek", cp_single_2627, 1},
    {"mugsquare", cp_single_2628, 1},
    {"muhiragana", cp_single_2629, 1},
    {"mukatakana", cp_single_2630, 1},
    {"mukatakanahalfwidth", cp_single_2631, 1},
    {"mulsquare", cp_single_2632, 1},
    {"multiply", cp_single_2633, 1},
    {"mumsquare", cp_single_2634, 1},
    {"munahhebrew", cp_single_2635, 1},
    {"munahlefthebrew", cp_single_2636, 1},
    {"musicalnote", cp_single_2637, 1},
    {"musicalnotedbl", cp_single_2638, 1},
    {"musicflatsign", cp_single_2639, 1},
    {"musicsharpsign", cp_single_2640, 1},
    {"mussquare", cp_single_2641, 1},
    {"muvsquare", cp_single_2642, 1},
    {"muwsquare", cp_single_2643, 1},
    {"mvmegasquare", cp_single_2644, 1},
    {"mvsquare", cp_single_2645, 1},
    {"mwmegasquare", cp_single_2646, 1},
    {"mwsquare", cp_single_2647, 1},
    {"n", cp_single_2648, 1},
    {"nabengali", cp_single_2649, 1},
    {"nabla", cp_single_2650, 1},
    {"nacute", cp_single_2651, 1},
    {"nadeva", cp_single_2652, 1},
    {"nagujarati", cp_single_2653, 1},
    {"nagurmukhi", cp_single_2654, 1},
    {"nahiragana", cp_single_2655, 1},
    {"nakatakana", cp_single_2656, 1},
    {"nakatakanahalfwidth", cp_single_2657, 1},
    {"napostrophe", cp_single_2658, 1},
    {"nasquare", cp_single_2659, 1},
    {"nbopomofo", cp_single_2660, 1},
    {"nbspace", cp_single_2661, 1},
    {"ncaron", cp_single_2662, 1},
    {"ncedilla", cp_single_2663, 1},
    {"ncircle", cp_single_2664, 1},
    {"ncircumflexbelow", cp_single_2665, 1},
    {"ncommaaccent", cp_single_2666, 1},
    {"ndotaccent", cp_single_2667, 1},
    {"ndotbelow", cp_single_2668, 1},
    {"nehiragana", cp_single_2669, 1},
    {"nekatakana", cp_single_2670, 1},
    {"nekatakanahalfwidth", cp_single_2671, 1},
    {"newsheqelsign", cp_single_2672, 1},
    {"nfsquare", cp_single_2673, 1},
    {"ngabengali", cp_single_2674, 1},
    {"ngadeva", cp_single_2675, 1},
    {"ngagujarati", cp_single_2676, 1},
    {"ngagurmukhi", cp_single_2677, 1},
    {"ngonguthai", cp_single_2678, 1},
    {"nhiragana", cp_single_2679, 1},
    {"nhookleft", cp_single_2680, 1},
    {"nhookretroflex", cp_single_2681, 1},
    {"nieunacirclekorean", cp_single_2682, 1},
    {"nieunaparenkorean", cp_single_2683, 1},
    {"nieuncieuckorean", cp_single_2684, 1},
    {"nieuncirclekorean", cp_single_2685, 1},
    {"nieunhieuhkorean", cp_single_2686, 1},
    {"nieunkorean", cp_single_2687, 1},
    {"nieunpansioskorean", cp_single_2688, 1},
    {"nieunparenkorean", cp_single_2689, 1},
    {"nieunsioskorean", cp_single_2690, 1},
    {"nieuntikeutkorean", cp_single_2691, 1},
    {"nihiragana", cp_single_2692, 1},
    {"nikatakana", cp_single_2693, 1},
    {"nikatakanahalfwidth", cp_single_2694, 1},
    {"nikhahitleftthai", cp_single_2695, 1},
    {"nikhahitthai", cp_single_2696, 1},
    {"nine", cp_single_2697, 1},
    {"ninearabic", cp_single_2698, 1},
    {"ninebengali", cp_single_2699, 1},
    {"ninecircle", cp_single_2700, 1},
    {"ninecircleinversesansserif", cp_single_2701, 1},
    {"ninedeva", cp_single_2702, 1},
    {"ninegujarati", cp_single_2703, 1},
    {"ninegurmukhi", cp_single_2704, 1},
    {"ninehackarabic", cp_single_2705, 1},
    {"ninehangzhou", cp_single_2706, 1},
    {"nineideographicparen", cp_single_2707, 1},
    {"nineinferior", cp_single_2708, 1},
    {"ninemonospace", cp_single_2709, 1},
    {"nineoldstyle", cp_single_2710, 1},
    {"nineparen", cp_single_2711, 1},
    {"nineperiod", cp_single_2712, 1},
    {"ninepersian", cp_single_2713, 1},
    {"nineroman", cp_single_2714, 1},
    {"ninesuperior", cp_single_2715, 1},
    {"nineteencircle", cp_single_2716, 1},
    {"nineteenparen", cp_single_2717, 1},
    {"nineteenperiod", cp_single_2718, 1},
    {"ninethai", cp_single_2719, 1},
    {"nj", cp_single_2720, 1},
    {"njecyrillic", cp_single_2721, 1},
    {"nkatakana", cp_single_2722, 1},
    {"nkatakanahalfwidth", cp_single_2723, 1},
    {"nlegrightlong", cp_single_2724, 1},
    {"nlinebelow", cp_single_2725, 1},
    {"nmonospace", cp_single_2726, 1},
    {"nmsquare", cp_single_2727, 1},
    {"nnabengali", cp_single_2728, 1},
    {"nnadeva", cp_single_2729, 1},
    {"nnagujarati", cp_single_2730, 1},
    {"nnagurmukhi", cp_single_2731, 1},
    {"nnnadeva", cp_single_2732, 1},
    {"nohiragana", cp_single_2733, 1},
    {"nokatakana", cp_single_2734, 1},
    {"nokatakanahalfwidth", cp_single_2735, 1},
    {"nonbreakingspace", cp_single_2736, 1},
    {"nonenthai", cp_single_2737, 1},
    {"nonuthai", cp_single_2738, 1},
    {"noonarabic", cp_single_2739, 1},
    {"noonfinalarabic", cp_single_2740, 1},
    {"noonghunnaarabic", cp_single_2741, 1},
    {"noonghunnafinalarabic", cp_single_2742, 1},
    {"noonhehinitialarabic", cp_2780, 2},
    {"nooninitialarabic", cp_single_2743, 1},
    {"noonjeeminitialarabic", cp_single_2744, 1},
    {"noonjeemisolatedarabic", cp_single_2745, 1},
    {"noonmedialarabic", cp_single_2746, 1},
    {"noonmeeminitialarabic", cp_single_2747, 1},
    {"noonmeemisolatedarabic", cp_single_2748, 1},
    {"noonnoonfinalarabic", cp_single_2749, 1},
    {"notcontains", cp_single_2750, 1},
    {"notelement", cp_single_2751, 1},
    {"notelementof", cp_single_2752, 1},
    {"notequal", cp_single_2753, 1},
    {"notgreater", cp_single_2754, 1},
    {"notgreaternorequal", cp_single_2755, 1},
    {"notgreaternorless", cp_single_2756, 1},
    {"notidentical", cp_single_2757, 1},
    {"notless", cp_single_2758, 1},
    {"notlessnorequal", cp_single_2759, 1},
    {"notparallel", cp_single_2760, 1},
    {"notprecedes", cp_single_2761, 1},
    {"notsubset", cp_single_2762, 1},
    {"notsucceeds", cp_single_2763, 1},
    {"notsuperset", cp_single_2764, 1},
    {"nowarmenian", cp_single_2765, 1},
    {"nparen", cp_single_2766, 1},
    {"nssquare", cp_single_2767, 1},
    {"nsuperior", cp_single_2768, 1},
    {"ntilde", cp_single_2769, 1},
    {"nu", cp_single_2770, 1},
    {"nuhiragana", cp_single_2771, 1},
    {"nukatakana", cp_single_2772, 1},
    {"nukatakanahalfwidth", cp_single_2773, 1},
    {"nuktabengali", cp_single_2774, 1},
    {"nuktadeva", cp_single_2775, 1},
    {"nuktagujarati", cp_single_2776, 1},
    {"nuktagurmukhi", cp_single_2777, 1},
    {"numbersign", cp_single_2778, 1},
    {"numbersignmonospace", cp_single_2779, 1},
    {"numbersignsmall", cp_single_2780, 1},
    {"numeralsigngreek", cp_single_2781, 1},
    {"numeralsignlowergreek", cp_single_2782, 1},
    {"numero", cp_single_2783, 1},
    {"nun", cp_single_2784, 1},
    {"nundagesh", cp_single_2785, 1},
    {"nundageshhebrew", cp_single_2786, 1},
    {"nunhebrew", cp_single_2787, 1},
    {"nvsquare", cp_single_2788, 1},
    {"nwsquare", cp_single_2789, 1},
    {"nyabengali", cp_single_2790, 1},
    {"nyadeva", cp_single_2791, 1},
    {"nyagujarati", cp_single_2792, 1},
    {"nyagurmukhi", cp_single_2793, 1},
    {"o", cp_single_2794, 1},
    {"oacute", cp_single_2795, 1},
    {"oangthai", cp_single_2796, 1},
    {"obarred", cp_single_2797, 1},
    {"obarredcyrillic", cp_single_2798, 1},
    {"obarreddieresiscyrillic", cp_single_2799, 1},
    {"obengali", cp_single_2800, 1},
    {"obopomofo", cp_single_2801, 1},
    {"obreve", cp_single_2802, 1},
    {"ocandradeva", cp_single_2803, 1},
    {"ocandragujarati", cp_single_2804, 1},
    {"ocandravowelsigndeva", cp_single_2805, 1},
    {"ocandravowelsigngujarati", cp_single_2806, 1},
    {"ocaron", cp_single_2807, 1},
    {"ocircle", cp_single_2808, 1},
    {"ocircumflex", cp_single_2809, 1},
    {"ocircumflexacute", cp_single_2810, 1},
    {"ocircumflexdotbelow", cp_single_2811, 1},
    {"ocircumflexgrave", cp_single_2812, 1},
    {"ocircumflexhookabove", cp_single_2813, 1},
    {"ocircumflextilde", cp_single_2814, 1},
    {"ocyrillic", cp_single_2815, 1},
    {"odblacute", cp_single_2816, 1},
    {"odblgrave", cp_single_2817, 1},
    {"odeva", cp_single_2818, 1},
    {"odieresis", cp_single_2819, 1},
    {"odieresiscyrillic", cp_single_2820, 1},
    {"odotbelow", cp_single_2821, 1},
    {"oe", cp_single_2822, 1},
    {"oekorean", cp_single_2823, 1},
    {"ogonek", cp_single_2824, 1},
    {"ogonekcmb", cp_single_2825, 1},
    {"ograve", cp_single_2826, 1},
    {"ogujarati", cp_single_2827, 1},
    {"oharmenian", cp_single_2828, 1},
    {"ohiragana", cp_single_2829, 1},
    {"ohookabove", cp_single_2830, 1},
    {"ohorn", cp_single_2831, 1},
    {"ohornacute", cp_single_2832, 1},
    {"ohorndotbelow", cp_single_2833, 1},
    {"ohorngrave", cp_single_2834, 1},
    {"ohornhookabove", cp_single_2835, 1},
    {"ohorntilde", cp_single_2836, 1},
    {"ohungarumlaut", cp_single_2837, 1},
    {"oi", cp_single_2838, 1},
    {"oinvertedbreve", cp_single_2839, 1},
    {"okatakana", cp_single_2840, 1},
    {"okatakanahalfwidth", cp_single_2841, 1},
    {"okorean", cp_single_2842, 1},
    {"olehebrew", cp_single_2843, 1},
    {"omacron", cp_single_2844, 1},
    {"omacronacute", cp_single_2845, 1},
    {"omacrongrave", cp_single_2846, 1},
    {"omdeva", cp_single_2847, 1},
    {"omega", cp_single_2848, 1},
    {"omega1", cp_single_2849, 1},
    {"omegacyrillic", cp_single_2850, 1},
    {"omegalatinclosed", cp_single_2851, 1},
    {"omegaroundcyrillic", cp_single_2852, 1},
    {"omegatitlocyrillic", cp_single_2853, 1},
    {"omegatonos", cp_single_2854, 1},
    {"omgujarati", cp_single_2855, 1},
    {"omicron", cp_single_2856, 1},
    {"omicrontonos", cp_single_2857, 1},
    {"omonospace", cp_single_2858, 1},
    {"one", cp_single_2859, 1},
    {"onearabic", cp_single_2860, 1},
    {"onebengali", cp_single_2861, 1},
    {"onecircle", cp_single_2862, 1},
    {"onecircleinversesansserif", cp_single_2863, 1},
    {"onedeva", cp_single_2864, 1},
    {"onedotenleader", cp_single_2865, 1},
    {"oneeighth", cp_single_2866, 1},
    {"onefitted", cp_single_2867, 1},
    {"onegujarati", cp_single_2868, 1},
    {"onegurmukhi", cp_single_2869, 1},
    {"onehackarabic", cp_single_2870, 1},
    {"onehalf", cp_single_2871, 1},
    {"onehangzhou", cp_single_2872, 1},
    {"oneideographicparen", cp_single_2873, 1},
    {"oneinferior", cp_single_2874, 1},
    {"onemonospace", cp_single_2875, 1},
    {"onenumeratorbengali", cp_single_2876, 1},
    {"oneoldstyle", cp_single_2877, 1},
    {"oneparen", cp_single_2878, 1},
    {"oneperiod", cp_single_2879, 1},
    {"onepersian", cp_single_2880, 1},
    {"onequarter", cp_single_2881, 1},
    {"oneroman", cp_single_2882, 1},
    {"onesuperior", cp_single_2883, 1},
    {"onethai", cp_single_2884, 1},
    {"onethird", cp_single_2885, 1},
    {"oogonek", cp_single_2886, 1},
    {"oogonekmacron", cp_single_2887, 1},
    {"oogurmukhi", cp_single_2888, 1},
    {"oomatragurmukhi", cp_single_2889, 1},
    {"oopen", cp_single_2890, 1},
    {"oparen", cp_single_2891, 1},
    {"openbullet", cp_single_2892, 1},
    {"option", cp_single_2893, 1},
    {"ordfeminine", cp_single_2894, 1},
    {"ordmasculine", cp_single_2895, 1},
    {"orthogonal", cp_single_2896, 1},
    {"oshortdeva", cp_single_2897, 1},
    {"oshortvowelsigndeva", cp_single_2898, 1},
    {"oslash", cp_single_2899, 1},
    {"oslashacute", cp_single_2900, 1},
    {"osmallhiragana", cp_single_2901, 1},
    {"osmallkatakana", cp_single_2902, 1},
    {"osmallkatakanahalfwidth", cp_single_2903, 1},
    {"ostrokeacute", cp_single_2904, 1},
    {"osuperior", cp_single_2905, 1},
    {"otcyrillic", cp_single_2906, 1},
    {"otilde", cp_single_2907, 1},
    {"otildeacute", cp_single_2908, 1},
    {"otildedieresis", cp_single_2909, 1},
    {"oubopomofo", cp_single_2910, 1},
    {"overline", cp_single_2911, 1},
    {"overlinecenterline", cp_single_2912, 1},
    {"overlinecmb", cp_single_2913, 1},
    {"overlinedashed", cp_single_2914, 1},
    {"overlinedblwavy", cp_single_2915, 1},
    {"overlinewavy", cp_single_2916, 1},
    {"overscore", cp_single_2917, 1},
    {"ovowelsignbengali", cp_single_2918, 1},
    {"ovowelsigndeva", cp_single_2919, 1},
    {"ovowelsigngujarati", cp_single_2920, 1},
    {"p", cp_single_2921, 1},
    {"paampssquare", cp_single_2922, 1},
    {"paasentosquare", cp_single_2923, 1},
    {"pabengali", cp_single_2924, 1},
    {"pacute", cp_single_2925, 1},
    {"padeva", cp_single_2926, 1},
    {"pagedown", cp_single_2927, 1},
    {"pageup", cp_single_2928, 1},
    {"pagujarati", cp_single_2929, 1},
    {"pagurmukhi", cp_single_2930, 1},
    {"pahiragana", cp_single_2931, 1},
    {"paiyannoithai", cp_single_2932, 1},
    {"pakatakana", cp_single_2933, 1},
    {"palatalizationcyrilliccmb", cp_single_2934, 1},
    {"palochkacyrillic", cp_single_2935, 1},
    {"pansioskorean", cp_single_2936, 1},
    {"paragraph", cp_single_2937, 1},
    {"parallel", cp_single_2938, 1},
    {"parenleft", cp_single_2939, 1},
    {"parenleftaltonearabic", cp_single_2940, 1},
    {"parenleftbt", cp_single_2941, 1},
    {"parenleftex", cp_single_2942, 1},
    {"parenleftinferior", cp_single_2943, 1},
    {"parenleftmonospace", cp_single_2944, 1},
    {"parenleftsmall", cp_single_2945, 1},
    {"parenleftsuperior", cp_single_2946, 1},
    {"parenlefttp", cp_single_2947, 1},
    {"parenleftvertical", cp_single_2948, 1},
    {"parenright", cp_single_2949, 1},
    {"parenrightaltonearabic", cp_single_2950, 1},
    {"parenrightbt", cp_single_2951, 1},
    {"parenrightex", cp_single_2952, 1},
    {"parenrightinferior", cp_single_2953, 1},
    {"parenrightmonospace", cp_single_2954, 1},
    {"parenrightsmall", cp_single_2955, 1},
    {"parenrightsuperior", cp_single_2956, 1},
    {"parenrighttp", cp_single_2957, 1},
    {"parenrightvertical", cp_single_2958, 1},
    {"partialdiff", cp_single_2959, 1},
    {"paseqhebrew", cp_single_2960, 1},
    {"pashtahebrew", cp_single_2961, 1},
    {"pasquare", cp_single_2962, 1},
    {"patah", cp_single_2963, 1},
    {"patah11", cp_single_2964, 1},
    {"patah1d", cp_single_2965, 1},
    {"patah2a", cp_single_2966, 1},
    {"patahhebrew", cp_single_2967, 1},
    {"patahnarrowhebrew", cp_single_2968, 1},
    {"patahquarterhebrew", cp_single_2969, 1},
    {"patahwidehebrew", cp_single_2970, 1},
    {"pazerhebrew", cp_single_2971, 1},
    {"pbopomofo", cp_single_2972, 1},
    {"pcircle", cp_single_2973, 1},
    {"pdotaccent", cp_single_2974, 1},
    {"pe", cp_single_2975, 1},
    {"pecyrillic", cp_single_2976, 1},
    {"pedagesh", cp_single_2977, 1},
    {"pedageshhebrew", cp_single_2978, 1},
    {"peezisquare", cp_single_2979, 1},
    {"pefinaldageshhebrew", cp_single_2980, 1},
    {"peharabic", cp_single_2981, 1},
    {"peharmenian", cp_single_2982, 1},
    {"pehebrew", cp_single_2983, 1},
    {"pehfinalarabic", cp_single_2984, 1},
    {"pehinitialarabic", cp_single_2985, 1},
    {"pehiragana", cp_single_2986, 1},
    {"pehmedialarabic", cp_single_2987, 1},
    {"pekatakana", cp_single_2988, 1},
    {"pemiddlehookcyrillic", cp_single_2989, 1},
    {"perafehebrew", cp_single_2990, 1},
    {"percent", cp_single_2991, 1},
    {"percentarabic", cp_single_2992, 1},
    {"percentmonospace", cp_single_2993, 1},
    {"percentsmall", cp_single_2994, 1},
    {"period", cp_single_2995, 1},
    {"periodarmenian", cp_single_2996, 1},
    {"periodcentered", cp_single_2997, 1},
    {"periodhalfwidth", cp_single_2998, 1},
    {"periodinferior", cp_single_2999, 1},
    {"periodmonospace", cp_single_3000, 1},
    {"periodsmall", cp_single_3001, 1},
    {"periodsuperior", cp_single_3002, 1},
    {"perispomenigreekcmb", cp_single_3003, 1},
    {"perpendicular", cp_single_3004, 1},
    {"perthousand", cp_single_3005, 1},
    {"peseta", cp_single_3006, 1},
    {"pfsquare", cp_single_3007, 1},
    {"phabengali", cp_single_3008, 1},
    {"phadeva", cp_single_3009, 1},
    {"phagujarati", cp_single_3010, 1},
    {"phagurmukhi", cp_single_3011, 1},
    {"phi", cp_single_3012, 1},
    {"phi1", cp_single_3013, 1},
    {"phieuphacirclekorean", cp_single_3014, 1},
    {"phieuphaparenkorean", cp_single_3015, 1},
    {"phieuphcirclekorean", cp_single_3016, 1},
    {"phieuphkorean", cp_single_3017, 1},
    {"phieuphparenkorean", cp_single_3018, 1},
    {"philatin", cp_single_3019, 1},
    {"phinthuthai", cp_single_3020, 1},
    {"phisymbolgreek", cp_single_3021, 1},
    {"phook", cp_single_3022, 1},
    {"phophanthai", cp_single_3023, 1},
    {"phophungthai", cp_single_3024, 1},
    {"phosamphaothai", cp_single_3025, 1},
    {"pi", cp_single_3026, 1},
    {"pieupacirclekorean", cp_single_3027, 1},
    {"pieupaparenkorean", cp_single_3028, 1},
    {"pieupcieuckorean", cp_single_3029, 1},
    {"pieupcirclekorean", cp_single_3030, 1},
    {"pieupkiyeokkorean", cp_single_3031, 1},
    {"pieupkorean", cp_single_3032, 1},
    {"pieupparenkorean", cp_single_3033, 1},
    {"pieupsioskiyeokkorean", cp_single_3034, 1},
    {"pieupsioskorean", cp_single_3035, 1},
    {"pieupsiostikeutkorean", cp_single_3036, 1},
    {"pieupthieuthkorean", cp_single_3037, 1},
    {"pieuptikeutkorean", cp_single_3038, 1},
    {"pihiragana", cp_single_3039, 1},
    {"pikatakana", cp_single_3040, 1},
    {"pisymbolgreek", cp_single_3041, 1},
    {"piwrarmenian", cp_single_3042, 1},
    {"plus", cp_single_3043, 1},
    {"plusbelowcmb", cp_single_3044, 1},
    {"pluscircle", cp_single_3045, 1},
    {"plusminus", cp_single_3046, 1},
    {"plusmod", cp_single_3047, 1},
    {"plusmonospace", cp_single_3048, 1},
    {"plussmall", cp_single_3049, 1},
    {"plussuperior", cp_single_3050, 1},
    {"pmonospace", cp_single_3051, 1},
    {"pmsquare", cp_single_3052, 1},
    {"pohiragana", cp_single_3053, 1},
    {"pointingindexdownwhite", cp_single_3054, 1},
    {"pointingindexleftwhite", cp_single_3055, 1},
    {"pointingindexrightwhite", cp_single_3056, 1},
    {"pointingindexupwhite", cp_single_3057, 1},
    {"pokatakana", cp_single_3058, 1},
    {"poplathai", cp_single_3059, 1},
    {"postalmark", cp_single_3060, 1},
    {"postalmarkface", cp_single_3061, 1},
    {"pparen", cp_single_3062, 1},
    {"precedes", cp_single_3063, 1},
    {"prescription", cp_single_3064, 1},
    {"primemod", cp_single_3065, 1},
    {"primereversed", cp_single_3066, 1},
    {"product", cp_single_3067, 1},
    {"projective", cp_single_3068, 1},
    {"prolongedkana", cp_single_3069, 1},
    {"propellor", cp_single_3070, 1},
    {"propersubset", cp_single_3071, 1},
    {"propersuperset", cp_single_3072, 1},
    {"proportion", cp_single_3073, 1},
    {"proportional", cp_single_3074, 1},
    {"psi", cp_single_3075, 1},
    {"psicyrillic", cp_single_3076, 1},
    {"psilipneumatacyrilliccmb", cp_single_3077, 1},
    {"pssquare", cp_single_3078, 1},
    {"puhiragana", cp_single_3079, 1},
    {"pukatakana", cp_single_3080, 1},
    {"pvsquare", cp_single_3081, 1},
    {"pwsquare", cp_single_3082, 1},
    {"q", cp_single_3083, 1},
    {"qadeva", cp_single_3084, 1},
    {"qadmahebrew", cp_single_3085, 1},
    {"qafarabic", cp_single_3086, 1},
    {"qaffinalarabic", cp_single_3087, 1},
    {"qafinitialarabic", cp_single_3088, 1},
    {"qafmedialarabic", cp_single_3089, 1},
    {"qamats", cp_single_3090, 1},
    {"qamats10", cp_single_3091, 1},
    {"qamats1a", cp_single_3092, 1},
    {"qamats1c", cp_single_3093, 1},
    {"qamats27", cp_single_3094, 1},
    {"qamats29", cp_single_3095, 1},
    {"qamats33", cp_single_3096, 1},
    {"qamatsde", cp_single_3097, 1},
    {"qamatshebrew", cp_single_3098, 1},
    {"qamatsnarrowhebrew", cp_single_3099, 1},
    {"qamatsqatanhebrew", cp_single_3100, 1},
    {"qamatsqatannarrowhebrew", cp_single_3101, 1},
    {"qamatsqatanquarterhebrew", cp_single_3102, 1},
    {"qamatsqatanwidehebrew", cp_single_3103, 1},
    {"qamatsquarterhebrew", cp_single_3104, 1},
    {"qamatswidehebrew", cp_single_3105, 1},
    {"qarneyparahebrew", cp_single_3106, 1},
    {"qbopomofo", cp_single_3107, 1},
    {"qcircle", cp_single_3108, 1},
    {"qhook", cp_single_3109, 1},
    {"qmonospace", cp_single_3110, 1},
    {"qof", cp_single_3111, 1},
    {"qofdagesh", cp_single_3112, 1},
    {"qofdageshhebrew", cp_single_3113, 1},
    {"qofhatafpatah", cp_3152, 2},
    {"qofhatafpatahhebrew", cp_3153, 2},
    {"qofhatafsegol", cp_3154, 2},
    {"qofhatafsegolhebrew", cp_3155, 2},
    {"qofhebrew", cp_single_3114, 1},
    {"qofhiriq", cp_3157, 2},
    {"qofhiriqhebrew", cp_3158, 2},
    {"qofholam", cp_3159, 2},
    {"qofholamhebrew", cp_3160, 2},
    {"qofpatah", cp_3161, 2},
    {"qofpatahhebrew", cp_3162, 2},
    {"qofqamats", cp_3163, 2},
    {"qofqamatshebrew", cp_3164, 2},
    {"qofqubuts", cp_3165, 2},
    {"qofqubutshebrew", cp_3166, 2},
    {"qofsegol", cp_3167, 2},
    {"qofsegolhebrew", cp_3168, 2},
    {"qofsheva", cp_3169, 2},
    {"qofshevahebrew", cp_3170, 2},
    {"qoftsere", cp_3171, 2},
    {"qoftserehebrew", cp_3172, 2},
    {"qparen", cp_single_3115, 1},
    {"quarternote", cp_single_3116, 1},
    {"qubuts", cp_single_3117, 1},
    {"qubuts18", cp_single_3118, 1},
    {"qubuts25", cp_single_3119, 1},
    {"qubuts31", cp_single_3120, 1},
    {"qubutshebrew", cp_single_3121, 1},
    {"qubutsnarrowhebrew", cp_single_3122, 1},
    {"qubutsquarterhebrew", cp_single_3123, 1},
    {"qubutswidehebrew", cp_single_3124, 1},
    {"question", cp_single_3125, 1},
    {"questionarabic", cp_single_3126, 1},
    {"questionarmenian", cp_single_3127, 1},
    {"questiondown", cp_single_3128, 1},
    {"questiondownsmall", cp_single_3129, 1},
    {"questiongreek", cp_single_3130, 1},
    {"questionmonospace", cp_single_3131, 1},
    {"questionsmall", cp_single_3132, 1},
    {"quotedbl", cp_single_3133, 1},
    {"quotedblbase", cp_single_3134, 1},
    {"quotedblleft", cp_single_3135, 1},
    {"quotedblmonospace", cp_single_3136, 1},
    {"quotedblprime", cp_single_3137, 1},
    {"quotedblprimereversed", cp_single_3138, 1},
    {"quotedblright", cp_single_3139, 1},
    {"quoteleft", cp_single_3140, 1},
    {"quoteleftreversed", cp_single_3141, 1},
    {"quotereversed", cp_single_3142, 1},
    {"quoteright", cp_single_3143, 1},
    {"quoterightn", cp_single_3144, 1},
    {"quotesinglbase", cp_single_3145, 1},
    {"quotesingle", cp_single_3146, 1},
    {"quotesinglemonospace", cp_single_3147, 1},
    {"r", cp_single_3148, 1},
    {"raarmenian", cp_single_3149, 1},
    {"rabengali", cp_single_3150, 1},
    {"racute", cp_single_3151, 1},
    {"radeva", cp_single_3152, 1},
    {"radical", cp_single_3153, 1},
    {"radicalex", cp_single_3154, 1},
    {"radoverssquare", cp_single_3155, 1},
    {"radoverssquaredsquare", cp_single_3156, 1},
    {"radsquare", cp_single_3157, 1},
    {"rafe", cp_single_3158, 1},
    {"rafehebrew", cp_single_3159, 1},
    {"ragujarati", cp_single_3160, 1},
    {"ragurmukhi", cp_single_3161, 1},
    {"rahiragana", cp_single_3162, 1},
    {"rakatakana", cp_single_3163, 1},
    {"rakatakanahalfwidth", cp_single_3164, 1},
    {"ralowerdiagonalbengali", cp_single_3165, 1},
    {"ramiddlediagonalbengali", cp_single_3166, 1},
    {"ramshorn", cp_single_3167, 1},
    {"ratio", cp_single_3168, 1},
    {"rbopomofo", cp_single_3169, 1},
    {"rcaron", cp_single_3170, 1},
    {"rcedilla", cp_single_3171, 1},
    {"rcircle", cp_single_3172, 1},
    {"rcommaaccent", cp_single_3173, 1},
    {"rdblgrave", cp_single_3174, 1},
    {"rdotaccent", cp_single_3175, 1},
    {"rdotbelow", cp_single_3176, 1},
    {"rdotbelowmacron", cp_single_3177, 1},
    {"referencemark", cp_single_3178, 1},
    {"reflexsubset", cp_single_3179, 1},
    {"reflexsuperset", cp_single_3180, 1},
    {"registered", cp_single_3181, 1},
    {"registersans", cp_single_3182, 1},
    {"registerserif", cp_single_3183, 1},
    {"reharabic", cp_single_3184, 1},
    {"reharmenian", cp_single_3185, 1},
    {"rehfinalarabic", cp_single_3186, 1},
    {"rehiragana", cp_single_3187, 1},
    {"rehyehaleflamarabic", cp_3246, 4},
    {"rekatakana", cp_single_3188, 1},
    {"rekatakanahalfwidth", cp_single_3189, 1},
    {"resh", cp_single_3190, 1},
    {"reshdageshhebrew", cp_single_3191, 1},
    {"reshhatafpatah", cp_3251, 2},
    {"reshhatafpatahhebrew", cp_3252, 2},
    {"reshhatafsegol", cp_3253, 2},
    {"reshhatafsegolhebrew", cp_3254, 2},
    {"reshhebrew", cp_single_3192, 1},
    {"reshhiriq", cp_3256, 2},
    {"reshhiriqhebrew", cp_3257, 2},
    {"reshholam", cp_3258, 2},
    {"reshholamhebrew", cp_3259, 2},
    {"reshpatah", cp_3260, 2},
    {"reshpatahhebrew", cp_3261, 2},
    {"reshqamats", cp_3262, 2},
    {"reshqamatshebrew", cp_3263, 2},
    {"reshqubuts", cp_3264, 2},
    {"reshqubutshebrew", cp_3265, 2},
    {"reshsegol", cp_3266, 2},
    {"reshsegolhebrew", cp_3267, 2},
    {"reshsheva", cp_3268, 2},
    {"reshshevahebrew", cp_3269, 2},
    {"reshtsere", cp_3270, 2},
    {"reshtserehebrew", cp_3271, 2},
    {"reversedtilde", cp_single_3193, 1},
    {"reviahebrew", cp_single_3194, 1},
    {"reviamugrashhebrew", cp_single_3195, 1},
    {"revlogicalnot", cp_single_3196, 1},
    {"rfishhook", cp_single_3197, 1},
    {"rfishhookreversed", cp_single_3198, 1},
    {"rhabengali", cp_single_3199, 1},
    {"rhadeva", cp_single_3200, 1},
    {"rho", cp_single_3201, 1},
    {"rhook", cp_single_3202, 1},
    {"rhookturned", cp_single_3203, 1},
    {"rhookturnedsuperior", cp_single_3204, 1},
    {"rhosymbolgreek", cp_single_3205, 1},
    {"rhotichookmod", cp_single_3206, 1},
    {"rieulacirclekorean", cp_single_3207, 1},
    {"rieulaparenkorean", cp_single_3208, 1},
    {"rieulcirclekorean", cp_single_3209, 1},
    {"rieulhieuhkorean", cp_single_3210, 1},
    {"rieulkiyeokkorean", cp_single_3211, 1},
    {"rieulkiyeoksioskorean", cp_single_3212, 1},
    {"rieulkorean", cp_single_3213, 1},
    {"rieulmieumkorean", cp_single_3214, 1},
    {"rieulpansioskorean", cp_single_3215, 1},
    {"rieulparenkorean", cp_single_3216, 1},
    {"rieulphieuphkorean", cp_single_3217, 1},
    {"rieulpieupkorean", cp_single_3218, 1},
    {"rieulpieupsioskorean", cp_single_3219, 1},
    {"rieulsioskorean", cp_single_3220, 1},
    {"rieulthieuthkorean", cp_single_3221, 1},
    {"rieultikeutkorean", cp_single_3222, 1},
    {"rieulyeorinhieuhkorean", cp_single_3223, 1},
    {"rightangle", cp_single_3224, 1},
    {"righttackbelowcmb", cp_single_3225, 1},
    {"righttriangle", cp_single_3226, 1},
    {"rihiragana", cp_single_3227, 1},
    {"rikatakana", cp_single_3228, 1},
    {"rikatakanahalfwidth", cp_single_3229, 1},
    {"ring", cp_single_3230, 1},
    {"ringbelowcmb", cp_single_3231, 1},
    {"ringcmb", cp_single_3232, 1},
    {"ringhalfleft", cp_single_3233, 1},
    {"ringhalfleftarmenian", cp_single_3234, 1},
    {"ringhalfleftbelowcmb", cp_single_3235, 1},
    {"ringhalfleftcentered", cp_single_3236, 1},
    {"ringhalfright", cp_single_3237, 1},
    {"ringhalfrightbelowcmb", cp_single_3238, 1},
    {"ringhalfrightcentered", cp_single_3239, 1},
    {"rinvertedbreve", cp_single_3240, 1},
    {"rittorusquare", cp_single_3241, 1},
    {"rlinebelow", cp_single_3242, 1},
    {"rlongleg", cp_single_3243, 1},
    {"rlonglegturned", cp_single_3244, 1},
    {"rmonospace", cp_single_3245, 1},
    {"rohiragana", cp_single_3246, 1},
    {"rokatakana", cp_single_3247, 1},
    {"rokatakanahalfwidth", cp_single_3248, 1},
    {"roruathai", cp_single_3249, 1},
    {"rparen", cp_single_3250, 1},
    {"rrabengali", cp_single_3251, 1},
    {"rradeva", cp_single_3252, 1},
    {"rragurmukhi", cp_single_3253, 1},
    {"rreharabic", cp_single_3254, 1},
    {"rrehfinalarabic", cp_single_3255, 1},
    {"rrvocalicbengali", cp_single_3256, 1},
    {"rrvocalicdeva", cp_single_3257, 1},
    {"rrvocalicgujarati", cp_single_3258, 1},
    {"rrvocalicvowelsignbengali", cp_single_3259, 1},
    {"rrvocalicvowelsigndeva", cp_single_3260, 1},
    {"rrvocalicvowelsigngujarati", cp_single_3261, 1},
    {"rsuperior", cp_single_3262, 1},
    {"rtblock", cp_single_3263, 1},
    {"rturned", cp_single_3264, 1},
    {"rturnedsuperior", cp_single_3265, 1},
    {"ruhiragana", cp_single_3266, 1},
    {"rukatakana", cp_single_3267, 1},
    {"rukatakanahalfwidth", cp_single_3268, 1},
    {"rupeemarkbengali", cp_single_3269, 1},
    {"rupeesignbengali", cp_single_3270, 1},
    {"rupiah", cp_single_3271, 1},
    {"ruthai", cp_single_3272, 1},
    {"rvocalicbengali", cp_single_3273, 1},
    {"rvocalicdeva", cp_single_3274, 1},
    {"rvocalicgujarati", cp_single_3275, 1},
    {"rvocalicvowelsignbengali", cp_single_3276, 1},
    {"rvocalicvowelsigndeva", cp_single_3277, 1},
    {"rvocalicvowelsigngujarati", cp_single_3278, 1},
    {"s", cp_single_3279, 1},
    {"sabengali", cp_single_3280, 1},
    {"sacute", cp_single_3281, 1},
    {"sacutedotaccent", cp_single_3282, 1},
    {"sadarabic", cp_single_3283, 1},
    {"sadeva", cp_single_3284, 1},
    {"sadfinalarabic", cp_single_3285, 1},
    {"sadinitialarabic", cp_single_3286, 1},
    {"sadmedialarabic", cp_single_3287, 1},
    {"sagujarati", cp_single_3288, 1},
    {"sagurmukhi", cp_single_3289, 1},
    {"sahiragana", cp_single_3290, 1},
    {"sakatakana", cp_single_3291, 1},
    {"sakatakanahalfwidth", cp_single_3292, 1},
    {"sallallahoualayhewasallamarabic", cp_single_3293, 1},
    {"samekh", cp_single_3294, 1},
    {"samekhdagesh", cp_single_3295, 1},
    {"samekhdageshhebrew", cp_single_3296, 1},
    {"samekhhebrew", cp_single_3297, 1},
    {"saraaathai", cp_single_3298, 1},
    {"saraaethai", cp_single_3299, 1},
    {"saraaimaimalaithai", cp_single_3300, 1},
    {"saraaimaimuanthai", cp_single_3301, 1},
    {"saraamthai", cp_single_3302, 1},
    {"saraathai", cp_single_3303, 1},
    {"saraethai", cp_single_3304, 1},
    {"saraiileftthai", cp_single_3305, 1},
    {"saraiithai", cp_single_3306, 1},
    {"saraileftthai", cp_single_3307, 1},
    {"saraithai", cp_single_3308, 1},
    {"saraothai", cp_single_3309, 1},
    {"saraueeleftthai", cp_single_3310, 1},
    {"saraueethai", cp_single_3311, 1},
    {"saraueleftthai", cp_single_3312, 1},
    {"sarauethai", cp_single_3313, 1},
    {"sarauthai", cp_single_3314, 1},
    {"sarauuthai", cp_single_3315, 1},
    {"sbopomofo", cp_single_3316, 1},
    {"scaron", cp_single_3317, 1},
    {"scarondotaccent", cp_single_3318, 1},
    {"scedilla", cp_single_3319, 1},
    {"schwa", cp_single_3320, 1},
    {"schwacyrillic", cp_single_3321, 1},
    {"schwadieresiscyrillic", cp_single_3322, 1},
    {"schwahook", cp_single_3323, 1},
    {"scircle", cp_single_3324, 1},
    {"scircumflex", cp_single_3325, 1},
    {"scommaaccent", cp_single_3326, 1},
    {"sdotaccent", cp_single_3327, 1},
    {"sdotbelow", cp_single_3328, 1},
    {"sdotbelowdotaccent", cp_single_3329, 1},
    {"seagullbelowcmb", cp_single_3330, 1},
    {"second", cp_single_3331, 1},
    {"secondtonechinese", cp_single_3332, 1},
    {"section", cp_single_3333, 1},
    {"seenarabic", cp_single_3334, 1},
    {"seenfinalarabic", cp_single_3335, 1},
    {"seeninitialarabic", cp_single_3336, 1},
    {"seenmedialarabic", cp_single_3337, 1},
    {"segol", cp_single_3338, 1},
    {"segol13", cp_single_3339, 1},
    {"segol1f", cp_single_3340, 1},
    {"segol2c", cp_single_3341, 1},
    {"segolhebrew", cp_single_3342, 1},
    {"segolnarrowhebrew", cp_single_3343, 1},
    {"segolquarterhebrew", cp_single_3344, 1},
    {"segoltahebrew", cp_single_3345, 1},
    {"segolwidehebrew", cp_single_3346, 1},
    {"seharmenian", cp_single_3347, 1},
    {"sehiragana", cp_single_3348, 1},
    {"sekatakana", cp_single_3349, 1},
    {"sekatakanahalfwidth", cp_single_3350, 1},
    {"semicolon", cp_single_3351, 1},
    {"semicolonarabic", cp_single_3352, 1},
    {"semicolonmonospace", cp_single_3353, 1},
    {"semicolonsmall", cp_single_3354, 1},
    {"semivoicedmarkkana", cp_single_3355, 1},
    {"semivoicedmarkkanahalfwidth", cp_single_3356, 1},
    {"sentisquare", cp_single_3357, 1},
    {"sentosquare", cp_single_3358, 1},
    {"seven", cp_single_3359, 1},
    {"sevenarabic", cp_single_3360, 1},
    {"sevenbengali", cp_single_3361, 1},
    {"sevencircle", cp_single_3362, 1},
    {"sevencircleinversesansserif", cp_single_3363, 1},
    {"sevendeva", cp_single_3364, 1},
    {"seveneighths", cp_single_3365, 1},
    {"sevengujarati", cp_single_3366, 1},
    {"sevengurmukhi", cp_single_3367, 1},
    {"sevenhackarabic", cp_single_3368, 1},
    {"sevenhangzhou", cp_single_3369, 1},
    {"sevenideographicparen", cp_single_3370, 1},
    {"seveninferior", cp_single_3371, 1},
    {"sevenmonospace", cp_single_3372, 1},
    {"sevenoldstyle", cp_single_3373, 1},
    {"sevenparen", cp_single_3374, 1},
    {"sevenperiod", cp_single_3375, 1},
    {"sevenpersian", cp_single_3376, 1},
    {"sevenroman", cp_single_3377, 1},
    {"sevensuperior", cp_single_3378, 1},
    {"seventeencircle", cp_single_3379, 1},
    {"seventeenparen", cp_single_3380, 1},
    {"seventeenperiod", cp_single_3381, 1},
    {"seventhai", cp_single_3382, 1},
    {"sfthyphen", cp_single_3383, 1},
    {"shaarmenian", cp_single_3384, 1},
    {"shabengali", cp_single_3385, 1},
    {"shacyrillic", cp_single_3386, 1},
    {"shaddaarabic", cp_single_3387, 1},
    {"shaddadammaarabic", cp_single_3388, 1},
    {"shaddadammatanarabic", cp_single_3389, 1},
    {"shaddafathaarabic", cp_single_3390, 1},
    {"shaddafathatanarabic", cp_3470, 2},
    {"shaddakasraarabic", cp_single_3391, 1},
    {"shaddakasratanarabic", cp_single_3392, 1},
    {"shade", cp_single_3393, 1},
    {"shadedark", cp_single_3394, 1},
    {"shadelight", cp_single_3395, 1},
    {"shademedium", cp_single_3396, 1},
    {"shadeva", cp_single_3397, 1},
    {"shagujarati", cp_single_3398, 1},
    {"shagurmukhi", cp_single_3399, 1},
    {"shalshelethebrew", cp_single_3400, 1},
    {"shbopomofo", cp_single_3401, 1},
    {"shchacyrillic", cp_single_3402, 1},
    {"sheenarabic", cp_single_3403, 1},
    {"sheenfinalarabic", cp_single_3404, 1},
    {"sheeninitialarabic", cp_single_3405, 1},
    {"sheenmedialarabic", cp_single_3406, 1},
    {"sheicoptic", cp_single_3407, 1},
    {"sheqel", cp_single_3408, 1},
    {"sheqelhebrew", cp_single_3409, 1},
    {"sheva", cp_single_3410, 1},
    {"sheva115", cp_single_3411, 1},
    {"sheva15", cp_single_3412, 1},
    {"sheva22", cp_single_3413, 1},
    {"sheva2e", cp_single_3414, 1},
    {"shevahebrew", cp_single_3415, 1},
    {"shevanarrowhebrew", cp_single_3416, 1},
    {"shevaquarterhebrew", cp_single_3417, 1},
    {"shevawidehebrew", cp_single_3418, 1},
    {"shhacyrillic", cp_single_3419, 1},
    {"shimacoptic", cp_single_3420, 1},
    {"shin", cp_single_3421, 1},
    {"shindagesh", cp_single_3422, 1},
    {"shindageshhebrew", cp_single_3423, 1},
    {"shindageshshindot", cp_single_3424, 1},
    {"shindageshshindothebrew", cp_single_3425, 1},
    {"shindageshsindot", cp_single_3426, 1},
    {"shindageshsindothebrew", cp_single_3427, 1},
    {"shindothebrew", cp_single_3428, 1},
    {"shinhebrew", cp_single_3429, 1},
    {"shinshindot", cp_single_3430, 1},
    {"shinshindothebrew", cp_single_3431, 1},
    {"shinsindot", cp_single_3432, 1},
    {"shinsindothebrew", cp_single_3433, 1},
    {"shook", cp_single_3434, 1},
    {"sigma", cp_single_3435, 1},
    {"sigma1", cp_single_3436, 1},
    {"sigmafinal", cp_single_3437, 1},
    {"sigmalunatesymbolgreek", cp_single_3438, 1},
    {"sihiragana", cp_single_3439, 1},
    {"sikatakana", cp_single_3440, 1},
    {"sikatakanahalfwidth", cp_single_3441, 1},
    {"siluqhebrew", cp_single_3442, 1},
    {"siluqlefthebrew", cp_single_3443, 1},
    {"similar", cp_single_3444, 1},
    {"sindothebrew", cp_single_3445, 1},
    {"siosacirclekorean", cp_single_3446, 1},
    {"siosaparenkorean", cp_single_3447, 1},
    {"sioscieuckorean", cp_single_3448, 1},
    {"sioscirclekorean", cp_single_3449, 1},
    {"sioskiyeokkorean", cp_single_3450, 1},
    {"sioskorean", cp_single_3451, 1},
    {"siosnieunkorean", cp_single_3452, 1},
    {"siosparenkorean", cp_single_3453, 1},
    {"siospieupkorean", cp_single_3454, 1},
    {"siostikeutkorean", cp_single_3455, 1},
    {"six", cp_single_3456, 1},
    {"sixarabic", cp_single_3457, 1},
    {"sixbengali", cp_single_3458, 1},
    {"sixcircle", cp_single_3459, 1},
    {"sixcircleinversesansserif", cp_single_3460, 1},
    {"sixdeva", cp_single_3461, 1},
    {"sixgujarati", cp_single_3462, 1},
    {"sixgurmukhi", cp_single_3463, 1},
    {"sixhackarabic", cp_single_3464, 1},
    {"sixhangzhou", cp_single_3465, 1},
    {"sixideographicparen", cp_single_3466, 1},
    {"sixinferior", cp_single_3467, 1},
    {"sixmonospace", cp_single_3468, 1},
    {"sixoldstyle", cp_single_3469, 1},
    {"sixparen", cp_single_3470, 1},
    {"sixperiod", cp_single_3471, 1},
    {"sixpersian", cp_single_3472, 1},
    {"sixroman", cp_single_3473, 1},
    {"sixsuperior", cp_single_3474, 1},
    {"sixteencircle", cp_single_3475, 1},
    {"sixteencurrencydenominatorbengali", cp_single_3476, 1},
    {"sixteenparen", cp_single_3477, 1},
    {"sixteenperiod", cp_single_3478, 1},
    {"sixthai", cp_single_3479, 1},
    {"slash", cp_single_3480, 1},
    {"slashmonospace", cp_single_3481, 1},
    {"slong", cp_single_3482, 1},
    {"slongdotaccent", cp_single_3483, 1},
    {"smileface", cp_single_3484, 1},
    {"smonospace", cp_single_3485, 1},
    {"sofpasuqhebrew", cp_single_3486, 1},
    {"softhyphen", cp_single_3487, 1},
    {"softsigncyrillic", cp_single_3488, 1},
    {"sohiragana", cp_single_3489, 1},
    {"sokatakana", cp_single_3490, 1},
    {"sokatakanahalfwidth", cp_single_3491, 1},
    {"soliduslongoverlaycmb", cp_single_3492, 1},
    {"solidusshortoverlaycmb", cp_single_3493, 1},
    {"sorusithai", cp_single_3494, 1},
    {"sosalathai", cp_single_3495, 1},
    {"sosothai", cp_single_3496, 1},
    {"sosuathai", cp_single_3497, 1},
    {"space", cp_single_3498, 1},
    {"spacehackarabic", cp_single_3499, 1},
    {"spade", cp_single_3500, 1},
    {"spadesuitblack", cp_single_3501, 1},
    {"spadesuitwhite", cp_single_3502, 1},
    {"sparen", cp_single_3503, 1},
    {"squarebelowcmb", cp_single_3504, 1},
    {"squarecc", cp_single_3505, 1},
    {"squarecm", cp_single_3506, 1},
    {"squarediagonalcrosshatchfill", cp_single_3507, 1},
    {"squarehorizontalfill", cp_single_3508, 1},
    {"squarekg", cp_single_3509, 1},
    {"squarekm", cp_single_3510, 1},
    {"squarekmcapital", cp_single_3511, 1},
    {"squareln", cp_single_3512, 1},
    {"squarelog", cp_single_3513, 1},
    {"squaremg", cp_single_3514, 1},
    {"squaremil", cp_single_3515, 1},
    {"squaremm", cp_single_3516, 1},
    {"squaremsquared", cp_single_3517, 1},
    {"squareorthogonalcrosshatchfill", cp_single_3518, 1},
    {"squareupperlefttolowerrightfill", cp_single_3519, 1},
    {"squareupperrighttolowerleftfill", cp_single_3520, 1},
    {"squareverticalfill", cp_single_3521, 1},
    {"squarewhitewithsmallblack", cp_single_3522, 1},
    {"srsquare", cp_single_3523, 1},
    {"ssabengali", cp_single_3524, 1},
    {"ssadeva", cp_single_3525, 1},
    {"ssagujarati", cp_single_3526, 1},
    {"ssangcieuckorean", cp_single_3527, 1},
    {"ssanghieuhkorean", cp_single_3528, 1},
    {"ssangieungkorean", cp_single_3529, 1},
    {"ssangkiyeokkorean", cp_single_3530, 1},
    {"ssangnieunkorean", cp_single_3531, 1},
    {"ssangpieupkorean", cp_single_3532, 1},
    {"ssangsioskorean", cp_single_3533, 1},
    {"ssangtikeutkorean", cp_single_3534, 1},
    {"ssuperior", cp_single_3535, 1},
    {"sterling", cp_single_3536, 1},
    {"sterlingmonospace", cp_single_3537, 1},
    {"strokelongoverlaycmb", cp_single_3538, 1},
    {"strokeshortoverlaycmb", cp_single_3539, 1},
    {"subset", cp_single_3540, 1},
    {"subsetnotequal", cp_single_3541, 1},
    {"subsetorequal", cp_single_3542, 1},
    {"succeeds", cp_single_3543, 1},
    {"suchthat", cp_single_3544, 1},
    {"suhiragana", cp_single_3545, 1},
    {"sukatakana", cp_single_3546, 1},
    {"sukatakanahalfwidth", cp_single_3547, 1},
    {"sukunarabic", cp_single_3548, 1},
    {"summation", cp_single_3549, 1},
    {"sun", cp_single_3550, 1},
    {"superset", cp_single_3551, 1},
    {"supersetnotequal", cp_single_3552, 1},
    {"supersetorequal", cp_single_3553, 1},
    {"svsquare", cp_single_3554, 1},
    {"syouwaerasquare", cp_single_3555, 1},
    {"t", cp_single_3556, 1},
    {"tabengali", cp_single_3557, 1},
    {"tackdown", cp_single_3558, 1},
    {"tackleft", cp_single_3559, 1},
    {"tadeva", cp_single_3560, 1},
    {"tagujarati", cp_single_3561, 1},
    {"tagurmukhi", cp_single_3562, 1},
    {"taharabic", cp_single_3563, 1},
    {"tahfinalarabic", cp_single_3564, 1},
    {"tahinitialarabic", cp_single_3565, 1},
    {"tahiragana", cp_single_3566, 1},
    {"tahmedialarabic", cp_single_3567, 1},
    {"taisyouerasquare", cp_single_3568, 1},
    {"takatakana", cp_single_3569, 1},
    {"takatakanahalfwidth", cp_single_3570, 1},
    {"tatweelarabic", cp_single_3571, 1},
    {"tau", cp_single_3572, 1},
    {"tav", cp_single_3573, 1},
    {"tavdages", cp_single_3574, 1},
    {"tavdagesh", cp_single_3575, 1},
    {"tavdageshhebrew", cp_single_3576, 1},
    {"tavhebrew", cp_single_3577, 1},
    {"tbar", cp_single_3578, 1},
    {"tbopomofo", cp_single_3579, 1},
    {"tcaron", cp_single_3580, 1},
    {"tccurl", cp_single_3581, 1},
    {"tcedilla", cp_single_3582, 1},
    {"tcheharabic", cp_single_3583, 1},
    {"tchehfinalarabic", cp_single_3584, 1},
    {"tchehinitialarabic", cp_single_3585, 1},
    {"tchehmedialarabic", cp_single_3586, 1},
    {"tchehmeeminitialarabic", cp_3667, 2},
    {"tcircle", cp_single_3587, 1},
    {"tcircumflexbelow", cp_single_3588, 1},
    {"tcommaaccent", cp_single_3589, 1},
    {"tdieresis", cp_single_3590, 1},
    {"tdotaccent", cp_single_3591, 1},
    {"tdotbelow", cp_single_3592, 1},
    {"tecyrillic", cp_single_3593, 1},
    {"tedescendercyrillic", cp_single_3594, 1},
    {"teharabic", cp_single_3595, 1},
    {"tehfinalarabic", cp_single_3596, 1},
    {"tehhahinitialarabic", cp_single_3597, 1},
    {"tehhahisolatedarabic", cp_single_3598, 1},
    {"tehinitialarabic", cp_single_3599, 1},
    {"tehiragana", cp_single_3600, 1},
    {"tehjeeminitialarabic", cp_single_3601, 1},
    {"tehjeemisolatedarabic", cp_single_3602, 1},
    {"tehmarbutaarabic", cp_single_3603, 1},
    {"tehmarbutafinalarabic", cp_single_3604, 1},
    {"tehmedialarabic", cp_single_3605, 1},
    {"tehmeeminitialarabic", cp_single_3606, 1},
    {"tehmeemisolatedarabic", cp_single_3607, 1},
    {"tehnoonfinalarabic", cp_single_3608, 1},
    {"tekatakana", cp_single_3609, 1},
    {"tekatakanahalfwidth", cp_single_3610, 1},
    {"telephone", cp_single_3611, 1},
    {"telephoneblack", cp_single_3612, 1},
    {"telishagedolahebrew", cp_single_3613, 1},
    {"telishaqetanahebrew", cp_single_3614, 1},
    {"tencircle", cp_single_3615, 1},
    {"tenideographicparen", cp_single_3616, 1},
    {"tenparen", cp_single_3617, 1},
    {"tenperiod", cp_single_3618, 1},
    {"tenroman", cp_single_3619, 1},
    {"tesh", cp_single_3620, 1},
    {"tet", cp_single_3621, 1},
    {"tetdagesh", cp_single_3622, 1},
    {"tetdageshhebrew", cp_single_3623, 1},
    {"tethebrew", cp_single_3624, 1},
    {"tetsecyrillic", cp_single_3625, 1},
    {"tevirhebrew", cp_single_3626, 1},
    {"tevirlefthebrew", cp_single_3627, 1},
    {"thabengali", cp_single_3628, 1},
    {"thadeva", cp_single_3629, 1},
    {"thagujarati", cp_single_3630, 1},
    {"thagurmukhi", cp_single_3631, 1},
    {"thalarabic", cp_single_3632, 1},
    {"thalfinalarabic", cp_single_3633, 1},
    {"thanthakhatlowleftthai", cp_single_3634, 1},
    {"thanthakhatlowrightthai", cp_single_3635, 1},
    {"thanthakhatthai", cp_single_3636, 1},
    {"thanthakhatupperleftthai", cp_single_3637, 1},
    {"theharabic", cp_single_3638, 1},
    {"thehfinalarabic", cp_single_3639, 1},
    {"thehinitialarabic", cp_single_3640, 1},
    {"thehmedialarabic", cp_single_3641, 1},
    {"thereexists", cp_single_3642, 1},
    {"therefore", cp_single_3643, 1},
    {"theta", cp_single_3644, 1},
    {"theta1", cp_single_3645, 1},
    {"thetasymbolgreek", cp_single_3646, 1},
    {"thieuthacirclekorean", cp_single_3647, 1},
    {"thieuthaparenkorean", cp_single_3648, 1},
    {"thieuthcirclekorean", cp_single_3649, 1},
    {"thieuthkorean", cp_single_3650, 1},
    {"thieuthparenkorean", cp_single_3651, 1},
    {"thirteencircle", cp_single_3652, 1},
    {"thirteenparen", cp_single_3653, 1},
    {"thirteenperiod", cp_single_3654, 1},
    {"thonangmonthothai", cp_single_3655, 1},
    {"thook", cp_single_3656, 1},
    {"thophuthaothai", cp_single_3657, 1},
    {"thorn", cp_single_3658, 1},
    {"thothahanthai", cp_single_3659, 1},
    {"thothanthai", cp_single_3660, 1},
    {"thothongthai", cp_single_3661, 1},
    {"thothungthai", cp_single_3662, 1},
    {"thousandcyrillic", cp_single_3663, 1},
    {"thousandsseparatorarabic", cp_single_3664, 1},
    {"thousandsseparatorpersian", cp_single_3665, 1},
    {"three", cp_single_3666, 1},
    {"threearabic", cp_single_3667, 1},
    {"threebengali", cp_single_3668, 1},
    {"threecircle", cp_single_3669, 1},
    {"threecircleinversesansserif", cp_single_3670, 1},
    {"threedeva", cp_single_3671, 1},
    {"threeeighths", cp_single_3672, 1},
    {"threegujarati", cp_single_3673, 1},
    {"threegurmukhi", cp_single_3674, 1},
    {"threehackarabic", cp_single_3675, 1},
    {"threehangzhou", cp_single_3676, 1},
    {"threeideographicparen", cp_single_3677, 1},
    {"threeinferior", cp_single_3678, 1},
    {"threemonospace", cp_single_3679, 1},
    {"threenumeratorbengali", cp_single_3680, 1},
    {"threeoldstyle", cp_single_3681, 1},
    {"threeparen", cp_single_3682, 1},
    {"threeperiod", cp_single_3683, 1},
    {"threepersian", cp_single_3684, 1},
    {"threequarters", cp_single_3685, 1},
    {"threequartersemdash", cp_single_3686, 1},
    {"threeroman", cp_single_3687, 1},
    {"threesuperior", cp_single_3688, 1},
    {"threethai", cp_single_3689, 1},
    {"thzsquare", cp_single_3690, 1},
    {"tihiragana", cp_single_3691, 1},
    {"tikatakana", cp_single_3692, 1},
    {"tikatakanahalfwidth", cp_single_3693, 1},
    {"tikeutacirclekorean", cp_single_3694, 1},
    {"tikeutaparenkorean", cp_single_3695, 1},
    {"tikeutcirclekorean", cp_single_3696, 1},
    {"tikeutkorean", cp_single_3697, 1},
    {"tikeutparenkorean", cp_single_3698, 1},
    {"tilde", cp_single_3699, 1},
    {"tildebelowcmb", cp_single_3700, 1},
    {"tildecmb", cp_single_3701, 1},
    {"tildecomb", cp_single_3702, 1},
    {"tildedoublecmb", cp_single_3703, 1},
    {"tildeoperator", cp_single_3704, 1},
    {"tildeoverlaycmb", cp_single_3705, 1},
    {"tildeverticalcmb", cp_single_3706, 1},
    {"timescircle", cp_single_3707, 1},
    {"tipehahebrew", cp_single_3708, 1},
    {"tipehalefthebrew", cp_single_3709, 1},
    {"tippigurmukhi", cp_single_3710, 1},
    {"titlocyrilliccmb", cp_single_3711, 1},
    {"tiwnarmenian", cp_single_3712, 1},
    {"tlinebelow", cp_single_3713, 1},
    {"tmonospace", cp_single_3714, 1},
    {"toarmenian", cp_single_3715, 1},
    {"tohiragana", cp_single_3716, 1},
    {"tokatakana", cp_single_3717, 1},
    {"tokatakanahalfwidth", cp_single_3718, 1},
    {"tonebarextrahighmod", cp_single_3719, 1},
    {"tonebarextralowmod", cp_single_3720, 1},
    {"tonebarhighmod", cp_single_3721, 1},
    {"tonebarlowmod", cp_single_3722, 1},
    {"tonebarmidmod", cp_single_3723, 1},
    {"tonefive", cp_single_3724, 1},
    {"tonesix", cp_single_3725, 1},
    {"tonetwo", cp_single_3726, 1},
    {"tonos", cp_single_3727, 1},
    {"tonsquare", cp_single_3728, 1},
    {"topatakthai", cp_single_3729, 1},
    {"tortoiseshellbracketleft", cp_single_3730, 1},
    {"tortoiseshellbracketleftsmall", cp_single_3731, 1},
    {"tortoiseshellbracketleftvertical", cp_single_3732, 1},
    {"tortoiseshellbracketright", cp_single_3733, 1},
    {"tortoiseshellbracketrightsmall", cp_single_3734, 1},
    {"tortoiseshellbracketrightvertical", cp_single_3735, 1},
    {"totaothai", cp_single_3736, 1},
    {"tpalatalhook", cp_single_3737, 1},
    {"tparen", cp_single_3738, 1},
    {"trademark", cp_single_3739, 1},
    {"trademarksans", cp_single_3740, 1},
    {"trademarkserif", cp_single_3741, 1},
    {"tretroflexhook", cp_single_3742, 1},
    {"triagdn", cp_single_3743, 1},
    {"triaglf", cp_single_3744, 1},
    {"triagrt", cp_single_3745, 1},
    {"triagup", cp_single_3746, 1},
    {"ts", cp_single_3747, 1},
    {"tsadi", cp_single_3748, 1},
    {"tsadidagesh", cp_single_3749, 1},
    {"tsadidageshhebrew", cp_single_3750, 1},
    {"tsadihebrew", cp_single_3751, 1},
    {"tsecyrillic", cp_single_3752, 1},
    {"tsere", cp_single_3753, 1},
    {"tsere12", cp_single_3754, 1},
    {"tsere1e", cp_single_3755, 1},
    {"tsere2b", cp_single_3756, 1},
    {"tserehebrew", cp_single_3757, 1},
    {"tserenarrowhebrew", cp_single_3758, 1},
    {"tserequarterhebrew", cp_single_3759, 1},
    {"tserewidehebrew", cp_single_3760, 1},
    {"tshecyrillic", cp_single_3761, 1},
    {"tsuperior", cp_single_3762, 1},
    {"ttabengali", cp_single_3763, 1},
    {"ttadeva", cp_single_3764, 1},
    {"ttagujarati", cp_single_3765, 1},
    {"ttagurmukhi", cp_single_3766, 1},
    {"tteharabic", cp_single_3767, 1},
    {"ttehfinalarabic", cp_single_3768, 1},
    {"ttehinitialarabic", cp_single_3769, 1},
    {"ttehmedialarabic", cp_single_3770, 1},
    {"tthabengali", cp_single_3771, 1},
    {"tthadeva", cp_single_3772, 1},
    {"tthagujarati", cp_single_3773, 1},
    {"tthagurmukhi", cp_single_3774, 1},
    {"tturned", cp_single_3775, 1},
    {"tuhiragana", cp_single_3776, 1},
    {"tukatakana", cp_single_3777, 1},
    {"tukatakanahalfwidth", cp_single_3778, 1},
    {"tusmallhiragana", cp_single_3779, 1},
    {"tusmallkatakana", cp_single_3780, 1},
    {"tusmallkatakanahalfwidth", cp_single_3781, 1},
    {"twelvecircle", cp_single_3782, 1},
    {"twelveparen", cp_single_3783, 1},
    {"twelveperiod", cp_single_3784, 1},
    {"twelveroman", cp_single_3785, 1},
    {"twentycircle", cp_single_3786, 1},
    {"twentyhangzhou", cp_single_3787, 1},
    {"twentyparen", cp_single_3788, 1},
    {"twentyperiod", cp_single_3789, 1},
    {"two", cp_single_3790, 1},
    {"twoarabic", cp_single_3791, 1},
    {"twobengali", cp_single_3792, 1},
    {"twocircle", cp_single_3793, 1},
    {"twocircleinversesansserif", cp_single_3794, 1},
    {"twodeva", cp_single_3795, 1},
    {"twodotenleader", cp_single_3796, 1},
    {"twodotleader", cp_single_3797, 1},
    {"twodotleadervertical", cp_single_3798, 1},
    {"twogujarati", cp_single_3799, 1},
    {"twogurmukhi", cp_single_3800, 1},
    {"twohackarabic", cp_single_3801, 1},
    {"twohangzhou", cp_single_3802, 1},
    {"twoideographicparen", cp_single_3803, 1},
    {"twoinferior", cp_single_3804, 1},
    {"twomonospace", cp_single_3805, 1},
    {"twonumeratorbengali", cp_single_3806, 1},
    {"twooldstyle", cp_single_3807, 1},
    {"twoparen", cp_single_3808, 1},
    {"twoperiod", cp_single_3809, 1},
    {"twopersian", cp_single_3810, 1},
    {"tworoman", cp_single_3811, 1},
    {"twostroke", cp_single_3812, 1},
    {"twosuperior", cp_single_3813, 1},
    {"twothai", cp_single_3814, 1},
    {"twothirds", cp_single_3815, 1},
    {"u", cp_single_3816, 1},
    {"uacute", cp_single_3817, 1},
    {"ubar", cp_single_3818, 1},
    {"ubengali", cp_single_3819, 1},
    {"ubopomofo", cp_single_3820, 1},
    {"ubreve", cp_single_3821, 1},
    {"ucaron", cp_single_3822, 1},
    {"ucircle", cp_single_3823, 1},
    {"ucircumflex", cp_single_3824, 1},
    {"ucircumflexbelow", cp_single_3825, 1},
    {"ucyrillic", cp_single_3826, 1},
    {"udattadeva", cp_single_3827, 1},
    {"udblacute", cp_single_3828, 1},
    {"udblgrave", cp_single_3829, 1},
    {"udeva", cp_single_3830, 1},
    {"udieresis", cp_single_3831, 1},
    {"udieresisacute", cp_single_3832, 1},
    {"udieresisbelow", cp_single_3833, 1},
    {"udieresiscaron", cp_single_3834, 1},
    {"udieresiscyrillic", cp_single_3835, 1},
    {"udieresisgrave", cp_single_3836, 1},
    {"udieresismacron", cp_single_3837, 1},
    {"udotbelow", cp_single_3838, 1},
    {"ugrave", cp_single_3839, 1},
    {"ugujarati", cp_single_3840, 1},
    {"ugurmukhi", cp_single_3841, 1},
    {"uhiragana", cp_single_3842, 1},
    {"uhookabove", cp_single_3843, 1},
    {"uhorn", cp_single_3844, 1},
    {"uhornacute", cp_single_3845, 1},
    {"uhorndotbelow", cp_single_3846, 1},
    {"uhorngrave", cp_single_3847, 1},
    {"uhornhookabove", cp_single_3848, 1},
    {"uhorntilde", cp_single_3849, 1},
    {"uhungarumlaut", cp_single_3850, 1},
    {"uhungarumlautcyrillic", cp_single_3851, 1},
    {"uinvertedbreve", cp_single_3852, 1},
    {"ukatakana", cp_single_3853, 1},
    {"ukatakanahalfwidth", cp_single_3854, 1},
    {"ukcyrillic", cp_single_3855, 1},
    {"ukorean", cp_single_3856, 1},
    {"umacron", cp_single_3857, 1},
    {"umacroncyrillic", cp_single_3858, 1},
    {"umacrondieresis", cp_single_3859, 1},
    {"umatragurmukhi", cp_single_3860, 1},
    {"umonospace", cp_single_3861, 1},
    {"underscore", cp_single_3862, 1},
    {"underscoredbl", cp_single_3863, 1},
    {"underscoremonospace", cp_single_3864, 1},
    {"underscorevertical", cp_single_3865, 1},
    {"underscorewavy", cp_single_3866, 1},
    {"union", cp_single_3867, 1},
    {"universal", cp_single_3868, 1},
    {"uogonek", cp_single_3869, 1},
    {"uparen", cp_single_3870, 1},
    {"upblock", cp_single_3871, 1},
    {"upperdothebrew", cp_single_3872, 1},
    {"upsilon", cp_single_3873, 1},
    {"upsilondieresis", cp_single_3874, 1},
    {"upsilondieresistonos", cp_single_3875, 1},
    {"upsilonlatin", cp_single_3876, 1},
    {"upsilontonos", cp_single_3877, 1},
    {"uptackbelowcmb", cp_single_3878, 1},
    {"uptackmod", cp_single_3879, 1},
    {"uragurmukhi", cp_single_3880, 1},
    {"uring", cp_single_3881, 1},
    {"ushortcyrillic", cp_single_3882, 1},
    {"usmallhiragana", cp_single_3883, 1},
    {"usmallkatakana", cp_single_3884, 1},
    {"usmallkatakanahalfwidth", cp_single_3885, 1},
    {"ustraightcyrillic", cp_single_3886, 1},
    {"ustraightstrokecyrillic", cp_single_3887, 1},
    {"utilde", cp_single_3888, 1},
    {"utildeacute", cp_single_3889, 1},
    {"utildebelow", cp_single_3890, 1},
    {"uubengali", cp_single_3891, 1},
    {"uudeva", cp_single_3892, 1},
    {"uugujarati", cp_single_3893, 1},
    {"uugurmukhi", cp_single_3894, 1},
    {"uumatragurmukhi", cp_single_3895, 1},
    {"uuvowelsignbengali", cp_single_3896, 1},
    {"uuvowelsigndeva", cp_single_3897, 1},
    {"uuvowelsigngujarati", cp_single_3898, 1},
    {"uvowelsignbengali", cp_single_3899, 1},
    {"uvowelsigndeva", cp_single_3900, 1},
    {"uvowelsigngujarati", cp_single_3901, 1},
    {"v", cp_single_3902, 1},
    {"vadeva", cp_single_3903, 1},
    {"vagujarati", cp_single_3904, 1},
    {"vagurmukhi", cp_single_3905, 1},
    {"vakatakana", cp_single_3906, 1},
    {"vav", cp_single_3907, 1},
    {"vavdagesh", cp_single_3908, 1},
    {"vavdagesh65", cp_single_3909, 1},
    {"vavdageshhebrew", cp_single_3910, 1},
    {"vavhebrew", cp_single_3911, 1},
    {"vavholam", cp_single_3912, 1},
    {"vavholamhebrew", cp_single_3913, 1},
    {"vavvavhebrew", cp_single_3914, 1},
    {"vavyodhebrew", cp_single_3915, 1},
    {"vcircle", cp_single_3916, 1},
    {"vdotbelow", cp_single_3917, 1},
    {"vecyrillic", cp_single_3918, 1},
    {"veharabic", cp_single_3919, 1},
    {"vehfinalarabic", cp_single_3920, 1},
    {"vehinitialarabic", cp_single_3921, 1},
    {"vehmedialarabic", cp_single_3922, 1},
    {"vekatakana", cp_single_3923, 1},
    {"venus", cp_single_3924, 1},
    {"verticalbar", cp_single_3925, 1},
    {"verticallineabovecmb", cp_single_3926, 1},
    {"verticallinebelowcmb", cp_single_3927, 1},
    {"verticallinelowmod", cp_single_3928, 1},
    {"verticallinemod", cp_single_3929, 1},
    {"vewarmenian", cp_single_3930, 1},
    {"vhook", cp_single_3931, 1},
    {"vikatakana", cp_single_3932, 1},
    {"viramabengali", cp_single_3933, 1},
    {"viramadeva", cp_single_3934, 1},
    {"viramagujarati", cp_single_3935, 1},
    {"visargabengali", cp_single_3936, 1},
    {"visargadeva", cp_single_3937, 1},
    {"visargagujarati", cp_single_3938, 1},
    {"vmonospace", cp_single_3939, 1},
    {"voarmenian", cp_single_3940, 1},
    {"voicediterationhiragana", cp_single_3941, 1},
    {"voicediterationkatakana", cp_single_3942, 1},
    {"voicedmarkkana", cp_single_3943, 1},
    {"voicedmarkkanahalfwidth", cp_single_3944, 1},
    {"vokatakana", cp_single_3945, 1},
    {"vparen", cp_single_3946, 1},
    {"vtilde", cp_single_3947, 1},
    {"vturned", cp_single_3948, 1},
    {"vuhiragana", cp_single_3949, 1},
    {"vukatakana", cp_single_3950, 1},
    {"w", cp_single_3951, 1},
    {"wacute", cp_single_3952, 1},
    {"waekorean", cp_single_3953, 1},
    {"wahiragana", cp_single_3954, 1},
    {"wakatakana", cp_single_3955, 1},
    {"wakatakanahalfwidth", cp_single_3956, 1},
    {"wakorean", cp_single_3957, 1},
    {"wasmallhiragana", cp_single_3958, 1},
    {"wasmallkatakana", cp_single_3959, 1},
    {"wattosquare", cp_single_3960, 1},
    {"wavedash", cp_single_3961, 1},
    {"wavyunderscorevertical", cp_single_3962, 1},
    {"wawarabic", cp_single_3963, 1},
    {"wawfinalarabic", cp_single_3964, 1},
    {"wawhamzaabovearabic", cp_single_3965, 1},
    {"wawhamzaabovefinalarabic", cp_single_3966, 1},
    {"wbsquare", cp_single_3967, 1},
    {"wcircle", cp_single_3968, 1},
    {"wcircumflex", cp_single_3969, 1},
    {"wdieresis", cp_single_3970, 1},
    {"wdotaccent", cp_single_3971, 1},
    {"wdotbelow", cp_single_3972, 1},
    {"wehiragana", cp_single_3973, 1},
    {"weierstrass", cp_single_3974, 1},
    {"wekatakana", cp_single_3975, 1},
    {"wekorean", cp_single_3976, 1},
    {"weokorean", cp_single_3977, 1},
    {"wgrave", cp_single_3978, 1},
    {"whitebullet", cp_single_3979, 1},
    {"whitecircle", cp_single_3980, 1},
    {"whitecircleinverse", cp_single_3981, 1},
    {"whitecornerbracketleft", cp_single_3982, 1},
    {"whitecornerbracketleftvertical", cp_single_3983, 1},
    {"whitecornerbracketright", cp_single_3984, 1},
    {"whitecornerbracketrightvertical", cp_single_3985, 1},
    {"whitediamond", cp_single_3986, 1},
    {"whitediamondcontainingblacksmalldiamond", cp_single_3987, 1},
    {"whitedownpointingsmalltriangle", cp_single_3988, 1},
    {"whitedownpointingtriangle", cp_single_3989, 1},
    {"whiteleftpointingsmalltriangle", cp_single_3990, 1},
    {"whiteleftpointingtriangle", cp_single_3991, 1},
    {"whitelenticularbracketleft", cp_single_3992, 1},
    {"whitelenticularbracketright", cp_single_3993, 1},
    {"whiterightpointingsmalltriangle", cp_single_3994, 1},
    {"whiterightpointingtriangle", cp_single_3995, 1},
    {"whitesmallsquare", cp_single_3996, 1},
    {"whitesmilingface", cp_single_3997, 1},
    {"whitesquare", cp_single_3998, 1},
    {"whitestar", cp_single_3999, 1},
    {"whitetelephone", cp_single_4000, 1},
    {"whitetortoiseshellbracketleft", cp_single_4001, 1},
    {"whitetortoiseshellbracketright", cp_single_4002, 1},
    {"whiteuppointingsmalltriangle", cp_single_4003, 1},
    {"whiteuppointingtriangle", cp_single_4004, 1},
    {"wihiragana", cp_single_4005, 1},
    {"wikatakana", cp_single_4006, 1},
    {"wikorean", cp_single_4007, 1},
    {"wmonospace", cp_single_4008, 1},
    {"wohiragana", cp_single_4009, 1},
    {"wokatakana", cp_single_4010, 1},
    {"wokatakanahalfwidth", cp_single_4011, 1},
    {"won", cp_single_4012, 1},
    {"wonmonospace", cp_single_4013, 1},
    {"wowaenthai", cp_single_4014, 1},
    {"wparen", cp_single_4015, 1},
    {"wring", cp_single_4016, 1},
    {"wsuperior", cp_single_4017, 1},
    {"wturned", cp_single_4018, 1},
    {"wynn", cp_single_4019, 1},
    {"x", cp_single_4020, 1},
    {"xabovecmb", cp_single_4021, 1},
    {"xbopomofo", cp_single_4022, 1},
    {"xcircle", cp_single_4023, 1},
    {"xdieresis", cp_single_4024, 1},
    {"xdotaccent", cp_single_4025, 1},
    {"xeharmenian", cp_single_4026, 1},
    {"xi", cp_single_4027, 1},
    {"xmonospace", cp_single_4028, 1},
    {"xparen", cp_single_4029, 1},
    {"xsuperior", cp_single_4030, 1},
    {"y", cp_single_4031, 1},
    {"yaadosquare", cp_single_4032, 1},
    {"yabengali", cp_single_4033, 1},
    {"yacute", cp_single_4034, 1},
    {"yadeva", cp_single_4035, 1},
    {"yaekorean", cp_single_4036, 1},
    {"yagujarati", cp_single_4037, 1},
    {"yagurmukhi", cp_single_4038, 1},
    {"yahiragana", cp_single_4039, 1},
    {"yakatakana", cp_single_4040, 1},
    {"yakatakanahalfwidth", cp_single_4041, 1},
    {"yakorean", cp_single_4042, 1},
    {"yamakkanthai", cp_single_4043, 1},
    {"yasmallhiragana", cp_single_4044, 1},
    {"yasmallkatakana", cp_single_4045, 1},
    {"yasmallkatakanahalfwidth", cp_single_4046, 1},
    {"yatcyrillic", cp_single_4047, 1},
    {"ycircle", cp_single_4048, 1},
    {"ycircumflex", cp_single_4049, 1},
    {"ydieresis", cp_single_4050, 1},
    {"ydotaccent", cp_single_4051, 1},
    {"ydotbelow", cp_single_4052, 1},
    {"yeharabic", cp_single_4053, 1},
    {"yehbarreearabic", cp_single_4054, 1},
    {"yehbarreefinalarabic", cp_single_4055, 1},
    {"yehfinalarabic", cp_single_4056, 1},
    {"yehhamzaabovearabic", cp_single_4057, 1},
    {"yehhamzaabovefinalarabic", cp_single_4058, 1},
    {"yehhamzaaboveinitialarabic", cp_single_4059, 1},
    {"yehhamzaabovemedialarabic", cp_single_4060, 1},
    {"yehinitialarabic", cp_single_4061, 1},
    {"yehmedialarabic", cp_single_4062, 1},
    {"yehmeeminitialarabic", cp_single_4063, 1},
    {"yehmeemisolatedarabic", cp_single_4064, 1},
    {"yehnoonfinalarabic", cp_single_4065, 1},
    {"yehthreedotsbelowarabic", cp_single_4066, 1},
    {"yekorean", cp_single_4067, 1},
    {"yen", cp_single_4068, 1},
    {"yenmonospace", cp_single_4069, 1},
    {"yeokorean", cp_single_4070, 1},
    {"yeorinhieuhkorean", cp_single_4071, 1},
    {"yerahbenyomohebrew", cp_single_4072, 1},
    {"yerahbenyomolefthebrew", cp_single_4073, 1},
    {"yericyrillic", cp_single_4074, 1},
    {"yerudieresiscyrillic", cp_single_4075, 1},
    {"yesieungkorean", cp_single_4076, 1},
    {"yesieungpansioskorean", cp_single_4077, 1},
    {"yesieungsioskorean", cp_single_4078, 1},
    {"yetivhebrew", cp_single_4079, 1},
    {"ygrave", cp_single_4080, 1},
    {"yhook", cp_single_4081, 1},
    {"yhookabove", cp_single_4082, 1},
    {"yiarmenian", cp_single_4083, 1},
    {"yicyrillic", cp_single_4084, 1},
    {"yikorean", cp_single_4085, 1},
    {"yinyang", cp_single_4086, 1},
    {"yiwnarmenian", cp_single_4087, 1},
    {"ymonospace", cp_single_4088, 1},
    {"yod", cp_single_4089, 1},
    {"yoddagesh", cp_single_4090, 1},
    {"yoddageshhebrew", cp_single_4091, 1},
    {"yodhebrew", cp_single_4092, 1},
    {"yodyodhebrew", cp_single_4093, 1},
    {"yodyodpatahhebrew", cp_single_4094, 1},
    {"yohiragana", cp_single_4095, 1},
    {"yoikorean", cp_single_4096, 1},
    {"yokatakana", cp_single_4097, 1},
    {"yokatakanahalfwidth", cp_single_4098, 1},
    {"yokorean", cp_single_4099, 1},
    {"yosmallhiragana", cp_single_4100, 1},
    {"yosmallkatakana", cp_single_4101, 1},
    {"yosmallkatakanahalfwidth", cp_single_4102, 1},
    {"yotgreek", cp_single_4103, 1},
    {"yoyaekorean", cp_single_4104, 1},
    {"yoyakorean", cp_single_4105, 1},
    {"yoyakthai", cp_single_4106, 1},
    {"yoyingthai", cp_single_4107, 1},
    {"yparen", cp_single_4108, 1},
    {"ypogegrammeni", cp_single_4109, 1},
    {"ypogegrammenigreekcmb", cp_single_4110, 1},
    {"yr", cp_single_4111, 1},
    {"yring", cp_single_4112, 1},
    {"ysuperior", cp_single_4113, 1},
    {"ytilde", cp_single_4114, 1},
    {"yturned", cp_single_4115, 1},
    {"yuhiragana", cp_single_4116, 1},
    {"yuikorean", cp_single_4117, 1},
    {"yukatakana", cp_single_4118, 1},
    {"yukatakanahalfwidth", cp_single_4119, 1},
    {"yukorean", cp_single_4120, 1},
    {"yusbigcyrillic", cp_single_4121, 1},
    {"yusbigiotifiedcyrillic", cp_single_4122, 1},
    {"yuslittlecyrillic", cp_single_4123, 1},
    {"yuslittleiotifiedcyrillic", cp_single_4124, 1},
    {"yusmallhiragana", cp_single_4125, 1},
    {"yusmallkatakana", cp_single_4126, 1},
    {"yusmallkatakanahalfwidth", cp_single_4127, 1},
    {"yuyekorean", cp_single_4128, 1},
    {"yuyeokorean", cp_single_4129, 1},
    {"yyabengali", cp_single_4130, 1},
    {"yyadeva", cp_single_4131, 1},
    {"z", cp_single_4132, 1},
    {"zaarmenian", cp_single_4133, 1},
    {"zacute", cp_single_4134, 1},
    {"zadeva", cp_single_4135, 1},
    {"zagurmukhi", cp_single_4136, 1},
    {"zaharabic", cp_single_4137, 1},
    {"zahfinalarabic", cp_single_4138, 1},
    {"zahinitialarabic", cp_single_4139, 1},
    {"zahiragana", cp_single_4140, 1},
    {"zahmedialarabic", cp_single_4141, 1},
    {"zainarabic", cp_single_4142, 1},
    {"zainfinalarabic", cp_single_4143, 1},
    {"zakatakana", cp_single_4144, 1},
    {"zaqefgadolhebrew", cp_single_4145, 1},
    {"zaqefqatanhebrew", cp_single_4146, 1},
    {"zarqahebrew", cp_single_4147, 1},
    {"zayin", cp_single_4148, 1},
    {"zayindagesh", cp_single_4149, 1},
    {"zayindageshhebrew", cp_single_4150, 1},
    {"zayinhebrew", cp_single_4151, 1},
    {"zbopomofo", cp_single_4152, 1},
    {"zcaron", cp_single_4153, 1},
    {"zcircle", cp_single_4154, 1},
    {"zcircumflex", cp_single_4155, 1},
    {"zcurl", cp_single_4156, 1},
    {"zdot", cp_single_4157, 1},
    {"zdotaccent", cp_single_4158, 1},
    {"zdotbelow", cp_single_4159, 1},
    {"zecyrillic", cp_single_4160, 1},
    {"zedescendercyrillic", cp_single_4161, 1},
    {"zedieresiscyrillic", cp_single_4162, 1},
    {"zehiragana", cp_single_4163, 1},
    {"zekatakana", cp_single_4164, 1},
    {"zero", cp_single_4165, 1},
    {"zeroarabic", cp_single_4166, 1},
    {"zerobengali", cp_single_4167, 1},
    {"zerodeva", cp_single_4168, 1},
    {"zerogujarati", cp_single_4169, 1},
    {"zerogurmukhi", cp_single_4170, 1},
    {"zerohackarabic", cp_single_4171, 1},
    {"zeroinferior", cp_single_4172, 1},
    {"zeromonospace", cp_single_4173, 1},
    {"zerooldstyle", cp_single_4174, 1},
    {"zeropersian", cp_single_4175, 1},
    {"zerosuperior", cp_single_4176, 1},
    {"zerothai", cp_single_4177, 1},
    {"zerowidthjoiner", cp_single_4178, 1},
    {"zerowidthnonjoiner", cp_single_4179, 1},
    {"zerowidthspace", cp_single_4180, 1},
    {"zeta", cp_single_4181, 1},
    {"zhbopomofo", cp_single_4182, 1},
    {"zhearmenian", cp_single_4183, 1},
    {"zhebrevecyrillic", cp_single_4184, 1},
    {"zhecyrillic", cp_single_4185, 1},
    {"zhedescendercyrillic", cp_single_4186, 1},
    {"zhedieresiscyrillic", cp_single_4187, 1},
    {"zihiragana", cp_single_4188, 1},
    {"zikatakana", cp_single_4189, 1},
    {"zinorhebrew", cp_single_4190, 1},
    {"zlinebelow", cp_single_4191, 1},
    {"zmonospace", cp_single_4192, 1},
    {"zohiragana", cp_single_4193, 1},
    {"zokatakana", cp_single_4194, 1},
    {"zparen", cp_single_4195, 1},
    {"zretroflexhook", cp_single_4196, 1},
    {"zstroke", cp_single_4197, 1},
    {"zuhiragana", cp_single_4198, 1},
    {"zukatakana", cp_single_4199, 1},
};

const size_t AdobeGlyphListSize = sizeof(AdobeGlyphListData) / sizeof(GlyphListEntry);

} // anonymous namespace

void initAdobeGlyphList(Encoding& encoding) {
    for (size_t i = 0; i < AdobeGlyphListSize; ++i) {
        const auto& entry = AdobeGlyphListData[i];
        ULongVector list;
        for (size_t j = 0; j < entry.count; ++j) {
            list.push_back(entry.codepoints[j]);
        }
        encoding.AdobeGlyphList[entry.name] = list;
    }
}
