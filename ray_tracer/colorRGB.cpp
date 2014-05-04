
#include "colorRGB.hpp"

namespace ray_tracer {

	colorRGB::colorRGB() {
		r = 0, g = 0, b = 0;
	}

	colorRGB::colorRGB(double r_, double g_, double b_) {
		r = r_, g = g_, b = b_;
	}

	colorRGB::colorRGB(int color_) {
		b = ((color_ >> 0x00) & 0xff) / 255.0;
		g = ((color_ >> 0x08) & 0xff) / 255.0;
		r = ((color_ >> 0x10) & 0xff) / 255.0;
	}

	colorRGB colorRGB::clamp() const {
		double rr = r, gg = g, bb = b;

		if (rr > 1.0) rr = 1.0;
		if (bb > 1.0) bb = 1.0;
		if (gg > 1.0) gg = 1.0;
		if (rr < 0.0) rr = 0.0;
		if (bb < 0.0) bb = 0.0;
		if (gg < 0.0) gg = 0.0;
		return colorRGB(rr, gg, bb);
	}

	// Color source from: http://www.w3schools.com/html/html_colornames.asp
	
	colorRGB color_aliceblue = colorRGB(0.941176470588, 0.972549019608, 1.0);
	colorRGB color_antiquewhite = colorRGB(0.980392156863, 0.921568627451, 0.843137254902);
	colorRGB color_aqua = colorRGB(0.0, 1.0, 1.0);
	colorRGB color_aquamarine = colorRGB(0.498039215686, 1.0, 0.83137254902);
	colorRGB color_azure = colorRGB(0.941176470588, 1.0, 1.0);
	colorRGB color_beige = colorRGB(0.960784313725, 0.960784313725, 0.862745098039);
	colorRGB color_bisque = colorRGB(1.0, 0.894117647059, 0.76862745098);
	colorRGB color_black = colorRGB(0.0, 0.0, 0.0);
	colorRGB color_blanchedalmond = colorRGB(1.0, 0.921568627451, 0.803921568627);
	colorRGB color_blue = colorRGB(0.0, 0.0, 1.0);
	colorRGB color_blueviolet = colorRGB(0.541176470588, 0.16862745098, 0.886274509804);
	colorRGB color_brown = colorRGB(0.647058823529, 0.164705882353, 0.164705882353);
	colorRGB color_burlywood = colorRGB(0.870588235294, 0.721568627451, 0.529411764706);
	colorRGB color_cadetblue = colorRGB(0.372549019608, 0.619607843137, 0.627450980392);
	colorRGB color_chartreuse = colorRGB(0.498039215686, 1.0, 0.0);
	colorRGB color_chocolate = colorRGB(0.823529411765, 0.411764705882, 0.117647058824);
	colorRGB color_coral = colorRGB(1.0, 0.498039215686, 0.313725490196);
	colorRGB color_cornflowerblue = colorRGB(0.392156862745, 0.58431372549, 0.929411764706);
	colorRGB color_cornsilk = colorRGB(1.0, 0.972549019608, 0.862745098039);
	colorRGB color_crimson = colorRGB(0.862745098039, 0.078431372549, 0.235294117647);
	colorRGB color_cyan = colorRGB(0.0, 1.0, 1.0);
	colorRGB color_darkblue = colorRGB(0.0, 0.0, 0.545098039216);
	colorRGB color_darkcyan = colorRGB(0.0, 0.545098039216, 0.545098039216);
	colorRGB color_darkgoldenrod = colorRGB(0.721568627451, 0.525490196078, 0.043137254902);
	colorRGB color_darkgray = colorRGB(0.662745098039, 0.662745098039, 0.662745098039);
	colorRGB color_darkgreen = colorRGB(0.0, 0.392156862745, 0.0);
	colorRGB color_darkkhaki = colorRGB(0.741176470588, 0.717647058824, 0.419607843137);
	colorRGB color_darkmagenta = colorRGB(0.545098039216, 0.0, 0.545098039216);
	colorRGB color_darkolivegreen = colorRGB(0.333333333333, 0.419607843137, 0.18431372549);
	colorRGB color_darkorange = colorRGB(1.0, 0.549019607843, 0.0);
	colorRGB color_darkorchid = colorRGB(0.6, 0.196078431373, 0.8);
	colorRGB color_darkred = colorRGB(0.545098039216, 0.0, 0.0);
	colorRGB color_darksalmon = colorRGB(0.913725490196, 0.588235294118, 0.478431372549);
	colorRGB color_darkseagreen = colorRGB(0.560784313725, 0.737254901961, 0.560784313725);
	colorRGB color_darkslateblue = colorRGB(0.282352941176, 0.239215686275, 0.545098039216);
	colorRGB color_darkslategray = colorRGB(0.18431372549, 0.309803921569, 0.309803921569);
	colorRGB color_darkturquoise = colorRGB(0.0, 0.807843137255, 0.819607843137);
	colorRGB color_darkviolet = colorRGB(0.580392156863, 0.0, 0.827450980392);
	colorRGB color_deeppink = colorRGB(1.0, 0.078431372549, 0.576470588235);
	colorRGB color_deepskyblue = colorRGB(0.0, 0.749019607843, 1.0);
	colorRGB color_dimgray = colorRGB(0.411764705882, 0.411764705882, 0.411764705882);
	colorRGB color_dodgerblue = colorRGB(0.117647058824, 0.564705882353, 1.0);
	colorRGB color_firebrick = colorRGB(0.698039215686, 0.133333333333, 0.133333333333);
	colorRGB color_floralwhite = colorRGB(1.0, 0.980392156863, 0.941176470588);
	colorRGB color_forestgreen = colorRGB(0.133333333333, 0.545098039216, 0.133333333333);
	colorRGB color_fuchsia = colorRGB(1.0, 0.0, 1.0);
	colorRGB color_gainsboro = colorRGB(0.862745098039, 0.862745098039, 0.862745098039);
	colorRGB color_ghostwhite = colorRGB(0.972549019608, 0.972549019608, 1.0);
	colorRGB color_gold = colorRGB(1.0, 0.843137254902, 0.0);
	colorRGB color_goldenrod = colorRGB(0.854901960784, 0.647058823529, 0.125490196078);
	colorRGB color_gray = colorRGB(0.501960784314, 0.501960784314, 0.501960784314);
	colorRGB color_green = colorRGB(0.0, 0.501960784314, 0.0);
	colorRGB color_greenyellow = colorRGB(0.678431372549, 1.0, 0.18431372549);
	colorRGB color_honeydew = colorRGB(0.941176470588, 1.0, 0.941176470588);
	colorRGB color_hotpink = colorRGB(1.0, 0.411764705882, 0.705882352941);
	colorRGB color_indianred  = colorRGB(0.803921568627, 0.360784313725, 0.360784313725);
	colorRGB color_indigo   = colorRGB(0.294117647059, 0.0, 0.509803921569);
	colorRGB color_ivory = colorRGB(1.0, 1.0, 0.941176470588);
	colorRGB color_khaki = colorRGB(0.941176470588, 0.901960784314, 0.549019607843);
	colorRGB color_lavender = colorRGB(0.901960784314, 0.901960784314, 0.980392156863);
	colorRGB color_lavenderblush = colorRGB(1.0, 0.941176470588, 0.960784313725);
	colorRGB color_lawngreen = colorRGB(0.486274509804, 0.988235294118, 0.0);
	colorRGB color_lemonchiffon = colorRGB(1.0, 0.980392156863, 0.803921568627);
	colorRGB color_lightblue = colorRGB(0.678431372549, 0.847058823529, 0.901960784314);
	colorRGB color_lightcoral = colorRGB(0.941176470588, 0.501960784314, 0.501960784314);
	colorRGB color_lightcyan = colorRGB(0.878431372549, 1.0, 1.0);
	colorRGB color_lightgoldenrodyellow = colorRGB(0.980392156863, 0.980392156863, 0.823529411765);
	colorRGB color_lightgray = colorRGB(0.827450980392, 0.827450980392, 0.827450980392);
	colorRGB color_lightgreen = colorRGB(0.564705882353, 0.933333333333, 0.564705882353);
	colorRGB color_lightpink = colorRGB(1.0, 0.713725490196, 0.756862745098);
	colorRGB color_lightsalmon = colorRGB(1.0, 0.627450980392, 0.478431372549);
	colorRGB color_lightseagreen = colorRGB(0.125490196078, 0.698039215686, 0.666666666667);
	colorRGB color_lightskyblue = colorRGB(0.529411764706, 0.807843137255, 0.980392156863);
	colorRGB color_lightslategray = colorRGB(0.466666666667, 0.533333333333, 0.6);
	colorRGB color_lightsteelblue = colorRGB(0.690196078431, 0.76862745098, 0.870588235294);
	colorRGB color_lightyellow = colorRGB(1.0, 1.0, 0.878431372549);
	colorRGB color_lime = colorRGB(0.0, 1.0, 0.0);
	colorRGB color_limegreen = colorRGB(0.196078431373, 0.803921568627, 0.196078431373);
	colorRGB color_linen = colorRGB(0.980392156863, 0.941176470588, 0.901960784314);
	colorRGB color_magenta = colorRGB(1.0, 0.0, 1.0);
	colorRGB color_maroon = colorRGB(0.501960784314, 0.0, 0.0);
	colorRGB color_mediumaquamarine = colorRGB(0.4, 0.803921568627, 0.666666666667);
	colorRGB color_mediumblue = colorRGB(0.0, 0.0, 0.803921568627);
	colorRGB color_mediumorchid = colorRGB(0.729411764706, 0.333333333333, 0.827450980392);
	colorRGB color_mediumpurple = colorRGB(0.576470588235, 0.439215686275, 0.858823529412);
	colorRGB color_mediumseagreen = colorRGB(0.235294117647, 0.701960784314, 0.443137254902);
	colorRGB color_mediumslateblue = colorRGB(0.482352941176, 0.407843137255, 0.933333333333);
	colorRGB color_mediumspringgreen = colorRGB(0.0, 0.980392156863, 0.603921568627);
	colorRGB color_mediumturquoise = colorRGB(0.282352941176, 0.819607843137, 0.8);
	colorRGB color_mediumvioletred = colorRGB(0.780392156863, 0.0823529411765, 0.521568627451);
	colorRGB color_midnightblue = colorRGB(0.0980392156863, 0.0980392156863, 0.439215686275);
	colorRGB color_mintcream = colorRGB(0.960784313725, 1.0, 0.980392156863);
	colorRGB color_mistyrose = colorRGB(1.0, 0.894117647059, 0.882352941176);
	colorRGB color_moccasin = colorRGB(1.0, 0.894117647059, 0.709803921569);
	colorRGB color_navajowhite = colorRGB(1.0, 0.870588235294, 0.678431372549);
	colorRGB color_navy = colorRGB(0.0, 0.0, 0.501960784314);
	colorRGB color_oldlace = colorRGB(0.992156862745, 0.960784313725, 0.901960784314);
	colorRGB color_olive = colorRGB(0.501960784314, 0.501960784314, 0.0);
	colorRGB color_olivedrab = colorRGB(0.419607843137, 0.556862745098, 0.137254901961);
	colorRGB color_orange = colorRGB(1.0, 0.647058823529, 0.0);
	colorRGB color_orangered = colorRGB(1.0, 0.270588235294, 0.0);
	colorRGB color_orchid = colorRGB(0.854901960784, 0.439215686275, 0.839215686275);
	colorRGB color_palegoldenrod = colorRGB(0.933333333333, 0.909803921569, 0.666666666667);
	colorRGB color_palegreen = colorRGB(0.596078431373, 0.98431372549, 0.596078431373);
	colorRGB color_paleturquoise = colorRGB(0.686274509804, 0.933333333333, 0.933333333333);
	colorRGB color_palevioletred = colorRGB(0.858823529412, 0.439215686275, 0.576470588235);
	colorRGB color_papayawhip = colorRGB(1.0, 0.937254901961, 0.835294117647);
	colorRGB color_peachpuff = colorRGB(1.0, 0.854901960784, 0.725490196078);
	colorRGB color_peru = colorRGB(0.803921568627, 0.521568627451, 0.247058823529);
	colorRGB color_pink = colorRGB(1.0, 0.752941176471, 0.796078431373);
	colorRGB color_plum = colorRGB(0.866666666667, 0.627450980392, 0.866666666667);
	colorRGB color_powderblue = colorRGB(0.690196078431, 0.878431372549, 0.901960784314);
	colorRGB color_purple = colorRGB(0.501960784314, 0.0, 0.501960784314);
	colorRGB color_red = colorRGB(1.0, 0.0, 0.0);
	colorRGB color_rosybrown = colorRGB(0.737254901961, 0.560784313725, 0.560784313725);
	colorRGB color_royalblue = colorRGB(0.254901960784, 0.411764705882, 0.882352941176);
	colorRGB color_saddlebrown = colorRGB(0.545098039216, 0.270588235294, 0.0745098039216);
	colorRGB color_salmon = colorRGB(0.980392156863, 0.501960784314, 0.447058823529);
	colorRGB color_sandybrown = colorRGB(0.956862745098, 0.643137254902, 0.376470588235);
	colorRGB color_seagreen = colorRGB(0.180392156863, 0.545098039216, 0.341176470588);
	colorRGB color_seashell = colorRGB(1.0, 0.960784313725, 0.933333333333);
	colorRGB color_sienna = colorRGB(0.627450980392, 0.321568627451, 0.176470588235);
	colorRGB color_silver = colorRGB(0.752941176471, 0.752941176471, 0.752941176471);
	colorRGB color_skyblue = colorRGB(0.529411764706, 0.807843137255, 0.921568627451);
	colorRGB color_slateblue = colorRGB(0.41568627451, 0.352941176471, 0.803921568627);
	colorRGB color_slategray = colorRGB(0.439215686275, 0.501960784314, 0.564705882353);
	colorRGB color_snow = colorRGB(1.0, 0.980392156863, 0.980392156863);
	colorRGB color_springgreen = colorRGB(0.0, 1.0, 0.498039215686);
	colorRGB color_steelblue = colorRGB(0.274509803922, 0.509803921569, 0.705882352941);
	colorRGB color_tan = colorRGB(0.823529411765, 0.705882352941, 0.549019607843);
	colorRGB color_teal = colorRGB(0.0, 0.501960784314, 0.501960784314);
	colorRGB color_thistle = colorRGB(0.847058823529, 0.749019607843, 0.847058823529);
	colorRGB color_tomato = colorRGB(1.0, 0.388235294118, 0.278431372549);
	colorRGB color_turquoise = colorRGB(0.250980392157, 0.878431372549, 0.81568627451);
	colorRGB color_violet = colorRGB(0.933333333333, 0.509803921569, 0.933333333333);
	colorRGB color_wheat = colorRGB(0.960784313725, 0.870588235294, 0.701960784314);
	colorRGB color_white = colorRGB(1.0, 1.0, 1.0);
	colorRGB color_whitesmoke = colorRGB(0.960784313725, 0.960784313725, 0.960784313725);
	colorRGB color_yellow = colorRGB(1.0, 1.0, 0.0);
	colorRGB color_yellowgreen = colorRGB(0.603921568627, 0.803921568627, 0.196078431373);
}
