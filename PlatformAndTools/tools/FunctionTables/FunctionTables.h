#pragma once

#include "Platform\lsWindows.h"

//It goes from 0.0f to 10.0f Negative values from -10.0f to 0.0f can be obtained by getting the abs(x) and making the result negative easy peasy!
f32 arctan[1001] = {
	0.000000f, 0.009999f, 0.019997f, 0.029991f, 0.039978f, 0.049958f, 0.059928f, 0.069886f,
	0.079829f, 0.089758f, 0.099668f, 0.109559f, 0.119428f, 0.129275f, 0.139095f, 0.148889f,
	0.158655f, 0.168390f, 0.178093f, 0.187762f, 0.197395f, 0.206992f, 0.216550f, 0.226068f,
	0.235545f, 0.244978f, 0.254368f, 0.263711f, 0.273008f, 0.282257f, 0.291456f, 0.300605f,
	0.309702f, 0.318747f, 0.327738f, 0.336674f, 0.345555f, 0.354379f, 0.363146f, 0.371856f,
	0.380506f, 0.389097f, 0.397627f, 0.406097f, 0.414506f, 0.422853f, 0.431138f, 0.439360f,
	0.447519f, 0.455615f, 0.463647f, 0.471615f, 0.479519f, 0.487358f, 0.495133f, 0.502843f,
	0.510488f, 0.518068f, 0.525583f, 0.533033f, 0.540419f, 0.547739f, 0.554995f, 0.562186f,
	0.569313f, 0.576375f, 0.583372f, 0.590306f, 0.597176f, 0.603982f, 0.610725f, 0.617405f,
	0.624022f, 0.630577f, 0.637070f, 0.643500f, 0.649870f, 0.656178f, 0.662426f, 0.668613f,
	0.674740f, 0.680808f, 0.686817f, 0.692767f, 0.698659f, 0.704493f, 0.710270f, 0.715990f,
	0.721654f, 0.727262f, 0.732814f, 0.738312f, 0.743755f, 0.749144f, 0.754479f, 0.759762f,
	0.764992f, 0.770170f, 0.775297f, 0.780372f, 0.785397f, 0.790373f, 0.795298f, 0.800175f,
	0.805003f, 0.809783f, 0.814515f, 0.819201f, 0.823840f, 0.828433f, 0.832980f, 0.837483f,
	0.841941f, 0.846355f, 0.850725f, 0.855052f, 0.859336f, 0.863579f, 0.867779f, 0.871939f,
	0.876057f, 0.880136f, 0.884174f, 0.888173f, 0.892133f, 0.896055f, 0.899938f, 0.903784f,
	0.907593f, 0.911364f, 0.915100f, 0.918799f, 0.922464f, 0.926093f, 0.929687f, 0.933247f,
	0.936773f, 0.940265f, 0.943725f, 0.947152f, 0.950546f, 0.953908f, 0.957239f, 0.960539f,
	0.963808f, 0.967046f, 0.970254f, 0.973433f, 0.976582f, 0.979702f, 0.982793f, 0.985856f,
	0.988890f, 0.991897f, 0.994877f, 0.997829f, 1.000755f, 1.003654f, 1.006527f, 1.009375f,
	1.012196f, 1.014993f, 1.017764f, 1.020511f, 1.023233f, 1.025932f, 1.028606f, 1.031257f,
	1.033885f, 1.036489f, 1.039071f, 1.041631f, 1.044168f, 1.046684f, 1.049177f, 1.051649f,
	1.054100f, 1.056530f, 1.058940f, 1.061329f, 1.063697f, 1.066046f, 1.068374f, 1.070683f,
	1.072973f, 1.075244f, 1.077496f, 1.079729f, 1.081943f, 1.084140f, 1.086318f, 1.088478f,
	1.090621f, 1.092746f, 1.094854f, 1.096944f, 1.099018f, 1.101075f, 1.103116f, 1.105140f,
	1.107148f, 1.109140f, 1.111116f, 1.113077f, 1.115022f, 1.116952f, 1.118866f, 1.120766f,
	1.122651f, 1.124521f, 1.126376f, 1.128218f, 1.130045f, 1.131858f, 1.133657f, 1.135442f,
	1.137214f, 1.138972f, 1.140717f, 1.142449f, 1.144168f, 1.145874f, 1.147567f, 1.149248f,
	1.150916f, 1.152571f, 1.154215f, 1.155846f, 1.157465f, 1.159073f, 1.160668f, 1.162252f,
	1.163825f, 1.165386f, 1.166936f, 1.168474f, 1.170002f, 1.171519f, 1.173025f, 1.174520f,
	1.176004f, 1.177479f, 1.178942f, 1.180396f, 1.181839f, 1.183272f, 1.184695f, 1.186108f,
	1.187511f, 1.188905f, 1.190289f, 1.191664f, 1.193029f, 1.194385f, 1.195731f, 1.197069f,
	1.198397f, 1.199717f, 1.201027f, 1.202329f, 1.203622f, 1.204906f, 1.206182f, 1.207449f,
	1.208708f, 1.209959f, 1.211201f, 1.212436f, 1.213662f, 1.214880f, 1.216090f, 1.217292f,
	1.218487f, 1.219674f, 1.220853f, 1.222025f, 1.223189f, 1.224345f, 1.225495f, 1.226637f,
	1.227772f, 1.228899f, 1.230020f, 1.231133f, 1.232240f, 1.233340f, 1.234432f, 1.235518f,
	1.236598f, 1.237670f, 1.238736f, 1.239796f, 1.240849f, 1.241895f, 1.242935f, 1.243969f,
	1.244997f, 1.246018f, 1.247033f, 1.248042f, 1.249045f, 1.250042f, 1.251033f, 1.252018f,
	1.252998f, 1.253971f, 1.254939f, 1.255901f, 1.256857f, 1.257808f, 1.258754f, 1.259693f,
	1.260628f, 1.261556f, 1.262480f, 1.263398f, 1.264311f, 1.265219f, 1.266121f, 1.267019f,
	1.267911f, 1.268798f, 1.269680f, 1.270557f, 1.271429f, 1.272297f, 1.273159f, 1.274017f,
	1.274870f, 1.275718f, 1.276561f, 1.277400f, 1.278234f, 1.279063f, 1.279888f, 1.280709f,
	1.281525f, 1.282336f, 1.283143f, 1.283946f, 1.284744f, 1.285538f, 1.286328f, 1.287113f,
	1.287895f, 1.288672f, 1.289445f, 1.290214f, 1.290979f, 1.291739f, 1.292496f, 1.293249f,
	1.293998f, 1.294742f, 1.295483f, 1.296220f, 1.296954f, 1.297683f, 1.298409f, 1.299131f,
	1.299849f, 1.300563f, 1.301274f, 1.301981f, 1.302685f, 1.303385f, 1.304081f, 1.304774f,
	1.305464f, 1.306150f, 1.306832f, 1.307511f, 1.308187f, 1.308859f, 1.309528f, 1.310193f,
	1.310856f, 1.311515f, 1.312170f, 1.312823f, 1.313472f, 1.314118f, 1.314761f, 1.315401f,
	1.316037f, 1.316671f, 1.317301f, 1.317929f, 1.318553f, 1.319175f, 1.319793f, 1.320408f,
	1.321021f, 1.321630f, 1.322237f, 1.322841f, 1.323442f, 1.324040f, 1.324635f, 1.325227f,
	1.325817f, 1.326404f, 1.326988f, 1.327569f, 1.328148f, 1.328724f, 1.329297f, 1.329868f,
	1.330436f, 1.331001f, 1.331564f, 1.332124f, 1.332682f, 1.333237f, 1.333790f, 1.334340f,
	1.334887f, 1.335432f, 1.335975f, 1.336515f, 1.337053f, 1.337588f, 1.338121f, 1.338651f,
	1.339180f, 1.339705f, 1.340229f, 1.340750f, 1.341269f, 1.341785f, 1.342299f, 1.342811f,
	1.343321f, 1.343829f, 1.344334f, 1.344837f, 1.345338f, 1.345836f, 1.346333f, 1.346827f,
	1.347320f, 1.347810f, 1.348298f, 1.348784f, 1.349267f, 1.349749f, 1.350229f, 1.350706f,
	1.351182f, 1.351656f, 1.352127f, 1.352597f, 1.353065f, 1.353530f, 1.353994f, 1.354456f,
	1.354915f, 1.355373f, 1.355829f, 1.356283f, 1.356736f, 1.357186f, 1.357634f, 1.358081f,
	1.358526f, 1.358969f, 1.359410f, 1.359849f, 1.360287f, 1.360723f, 1.361157f, 1.361589f,
	1.362019f, 1.362448f, 1.362875f, 1.363300f, 1.363724f, 1.364146f, 1.364566f, 1.364984f,
	1.365401f, 1.365816f, 1.366230f, 1.366642f, 1.367052f, 1.367460f, 1.367868f, 1.368273f,
	1.368677f, 1.369079f, 1.369479f, 1.369879f, 1.370276f, 1.370672f, 1.371066f, 1.371459f,
	1.371851f, 1.372240f, 1.372629f, 1.373016f, 1.373401f, 1.373785f, 1.374167f, 1.374548f,
	1.374928f, 1.375306f, 1.375683f, 1.376058f, 1.376431f, 1.376804f, 1.377175f, 1.377544f,
	1.377912f, 1.378279f, 1.378645f, 1.379009f, 1.379371f, 1.379733f, 1.380093f, 1.380451f,
	1.380809f, 1.381164f, 1.381519f, 1.381872f, 1.382224f, 1.382575f, 1.382925f, 1.383273f,
	1.383620f, 1.383966f, 1.384310f, 1.384653f, 1.384995f, 1.385336f, 1.385675f, 1.386013f,
	1.386350f, 1.386686f, 1.387021f, 1.387354f, 1.387686f, 1.388017f, 1.388347f, 1.388675f,
	1.389003f, 1.389329f, 1.389654f, 1.389978f, 1.390301f, 1.390623f, 1.390943f, 1.391263f,
	1.391581f, 1.391898f, 1.392214f, 1.392529f, 1.392843f, 1.393156f, 1.393468f, 1.393778f,
	1.394088f, 1.394397f, 1.394704f, 1.395010f, 1.395316f, 1.395620f, 1.395923f, 1.396225f,
	1.396526f, 1.396827f, 1.397126f, 1.397424f, 1.397721f, 1.398017f, 1.398312f, 1.398606f,
	1.398899f, 1.399191f, 1.399482f, 1.399773f, 1.400062f, 1.400350f, 1.400637f, 1.400924f,
	1.401209f, 1.401493f, 1.401777f, 1.402059f, 1.402341f, 1.402621f, 1.402901f, 1.403180f,
	1.403458f, 1.403735f, 1.404011f, 1.404286f, 1.404560f, 1.404834f, 1.405106f, 1.405378f,
	1.405648f, 1.405918f, 1.406187f, 1.406455f, 1.406722f, 1.406989f, 1.407254f, 1.407519f,
	1.407783f, 1.408046f, 1.408308f, 1.408569f, 1.408830f, 1.409089f, 1.409348f, 1.409606f,
	1.409863f, 1.410120f, 1.410375f, 1.410630f, 1.410884f, 1.411137f, 1.411390f, 1.411641f,
	1.411892f, 1.412142f, 1.412391f, 1.412640f, 1.412887f, 1.413134f, 1.413380f, 1.413626f,
	1.413870f, 1.414114f, 1.414357f, 1.414600f, 1.414841f, 1.415082f, 1.415322f, 1.415562f,
	1.415800f, 1.416038f, 1.416276f, 1.416512f, 1.416748f, 1.416983f, 1.417217f, 1.417451f,
	1.417684f, 1.417916f, 1.418148f, 1.418379f, 1.418609f, 1.418838f, 1.419067f, 1.419295f,
	1.419523f, 1.419749f, 1.419976f, 1.420201f, 1.420426f, 1.420650f, 1.420873f, 1.421096f,
	1.421318f, 1.421540f, 1.421760f, 1.421981f, 1.422200f, 1.422419f, 1.422637f, 1.422855f,
	1.423072f, 1.423288f, 1.423504f, 1.423719f, 1.423933f, 1.424147f, 1.424360f, 1.424573f,
	1.424785f, 1.424996f, 1.425207f, 1.425417f, 1.425627f, 1.425836f, 1.426044f, 1.426252f,
	1.426459f, 1.426666f, 1.426872f, 1.427077f, 1.427282f, 1.427486f, 1.427690f, 1.427893f,
	1.428096f, 1.428298f, 1.428499f, 1.428700f, 1.428900f, 1.429100f, 1.429299f, 1.429498f,
	1.429696f, 1.429893f, 1.430090f, 1.430287f, 1.430482f, 1.430678f, 1.430872f, 1.431067f,
	1.431261f, 1.431454f, 1.431646f, 1.431838f, 1.432030f, 1.432221f, 1.432412f, 1.432602f,
	1.432791f, 1.432980f, 1.433169f, 1.433357f, 1.433544f, 1.433731f, 1.433917f, 1.434103f,
	1.434289f, 1.434474f, 1.434658f, 1.434842f, 1.435026f, 1.435209f, 1.435391f, 1.435573f,
	1.435755f, 1.435936f, 1.436116f, 1.436296f, 1.436476f, 1.436655f, 1.436834f, 1.437012f,
	1.437189f, 1.437367f, 1.437543f, 1.437720f, 1.437895f, 1.438071f, 1.438246f, 1.438420f,
	1.438594f, 1.438768f, 1.438941f, 1.439113f, 1.439286f, 1.439457f, 1.439629f, 1.439799f,
	1.439970f, 1.440140f, 1.440309f, 1.440478f, 1.440647f, 1.440815f, 1.440983f, 1.441150f,
	1.441317f, 1.441484f, 1.441650f, 1.441816f, 1.441981f, 1.442146f, 1.442310f, 1.442474f,
	1.442638f, 1.442801f, 1.442963f, 1.443126f, 1.443288f, 1.443449f, 1.443610f, 1.443771f,
	1.443931f, 1.444091f, 1.444251f, 1.444410f, 1.444568f, 1.444727f, 1.444885f, 1.445042f,
	1.445199f, 1.445356f, 1.445512f, 1.445668f, 1.445824f, 1.445979f, 1.446134f, 1.446288f,
	1.446442f, 1.446596f, 1.446749f, 1.446902f, 1.447055f, 1.447207f, 1.447359f, 1.447510f,
	1.447661f, 1.447812f, 1.447962f, 1.448112f, 1.448262f, 1.448411f, 1.448560f, 1.448708f,
	1.448856f, 1.449004f, 1.449151f, 1.449299f, 1.449445f, 1.449592f, 1.449738f, 1.449883f,
	1.450029f, 1.450174f, 1.450318f, 1.450462f, 1.450606f, 1.450750f, 1.450893f, 1.451036f,
	1.451179f, 1.451321f, 1.451463f, 1.451604f, 1.451746f, 1.451887f, 1.452027f, 1.452167f,
	1.452307f, 1.452447f, 1.452586f, 1.452725f, 1.452864f, 1.453002f, 1.453140f, 1.453278f,
	1.453415f, 1.453552f, 1.453689f, 1.453825f, 1.453961f, 1.454097f, 1.454232f, 1.454367f,
	1.454502f, 1.454636f, 1.454771f, 1.454904f, 1.455038f, 1.455171f, 1.455304f, 1.455437f,
	1.455569f, 1.455701f, 1.455833f, 1.455964f, 1.456095f, 1.456226f, 1.456357f, 1.456487f,
	1.456617f, 1.456747f, 1.456876f, 1.457005f, 1.457134f, 1.457263f, 1.457391f, 1.457519f,
	1.457646f, 1.457774f, 1.457901f, 1.458027f, 1.458154f, 1.458280f, 1.458406f, 1.458532f,
	1.458657f, 1.458782f, 1.458907f, 1.459032f, 1.459156f, 1.459280f, 1.459403f, 1.459527f,
	1.459650f, 1.459773f, 1.459896f, 1.460018f, 1.460140f, 1.460262f, 1.460383f, 1.460505f,
	1.460626f, 1.460746f, 1.460867f, 1.460987f, 1.461107f, 1.461227f, 1.461346f, 1.461466f,
	1.461584f, 1.461703f, 1.461821f, 1.461940f, 1.462058f, 1.462175f, 1.462293f, 1.462410f,
	1.462527f, 1.462643f, 1.462760f, 1.462876f, 1.462992f, 1.463107f, 1.463223f, 1.463338f,
	1.463453f, 1.463568f, 1.463682f, 1.463796f, 1.463910f, 1.464024f, 1.464137f, 1.464250f,
	1.464363f, 1.464476f, 1.464589f, 1.464701f, 1.464813f, 1.464925f, 1.465036f, 1.465148f,
	1.465259f, 1.465370f, 1.465480f, 1.465591f, 1.465701f, 1.465811f, 1.465920f, 1.466030f,
	1.466139f, 1.466248f, 1.466357f, 1.466465f, 1.466574f, 1.466682f, 1.466790f, 1.466897f,
	1.467005f, 1.467112f, 1.467219f, 1.467326f, 1.467433f, 1.467539f, 1.467645f, 1.467751f,
	1.467857f, 1.467962f, 1.468067f, 1.468172f, 1.468277f, 1.468382f, 1.468486f, 1.468591f,
	1.468694f, 1.468798f, 1.468902f, 1.469005f, 1.469108f, 1.469211f, 1.469314f, 1.469417f,
	1.469519f, 1.469621f, 1.469723f, 1.469825f, 1.469926f, 1.470027f, 1.470129f, 1.470229f,
	1.470330f, 1.470431f, 1.470531f, 1.470631f, 1.470731f, 1.470831f, 1.470930f, 1.471029f,
	1.471129f };