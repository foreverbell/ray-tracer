#ifndef __COLORRGB_HPP__
#define __COLORRGB_HPP__

#include <cstdint>

namespace ray_tracer {

	class colorRGB {
	public:
		colorRGB();
		colorRGB(double, double, double);
		colorRGB(uint32_t);
		colorRGB clampRGB() const;
		friend colorRGB operator+(const colorRGB &, const colorRGB &);
		friend colorRGB &operator+=(colorRGB &, const colorRGB &);
		friend colorRGB operator-(const colorRGB &, const colorRGB &);
		friend colorRGB operator*(const colorRGB &, double);
		friend colorRGB operator*(double, const colorRGB &);
		friend colorRGB operator*(const colorRGB &, const colorRGB &);
		friend colorRGB operator/(const colorRGB &, double);
	public:
		double r, g, b;
	};

	inline colorRGB operator+(const colorRGB &c1, const colorRGB &c2) {
		return colorRGB(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
	}

	inline colorRGB &operator+=(colorRGB &c1, const colorRGB &c2) {
		c1.r += c2.r;
		c1.g += c2.g;
		c1.b += c2.b;
		return c1;
	}

	inline colorRGB operator-(const colorRGB &c1, const colorRGB &c2) {
		return colorRGB(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
	}

	inline colorRGB operator*(const colorRGB &c, double f) {
		return colorRGB(c.r * f, c.g * f, c.b * f);
	}

	inline colorRGB operator*(double f, const colorRGB &c) {
		return colorRGB(c.r * f, c.g * f, c.b * f);
	}

	inline colorRGB operator*(const colorRGB &c1, const colorRGB &c2) {
		return colorRGB(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
	}

	inline colorRGB operator/(const colorRGB &c, double f) {
		double inv = 1 / f;
		return colorRGB(c.r * inv, c.g * inv, c.b * inv);
	}

	// Color source from: http://www.w3schools.com/html/html_colornames.asp

	namespace color {
		const colorRGB aliceblue = colorRGB(0.941176470588, 0.972549019608, 1.0);
		const colorRGB antiquewhite = colorRGB(0.980392156863, 0.921568627451, 0.843137254902);
		const colorRGB aqua = colorRGB(0.0, 1.0, 1.0);
		const colorRGB aquamarine = colorRGB(0.498039215686, 1.0, 0.83137254902);
		const colorRGB azure = colorRGB(0.941176470588, 1.0, 1.0);
		const colorRGB beige = colorRGB(0.960784313725, 0.960784313725, 0.862745098039);
		const colorRGB bisque = colorRGB(1.0, 0.894117647059, 0.76862745098);
		const colorRGB black = colorRGB(0.0, 0.0, 0.0);
		const colorRGB blanchedalmond = colorRGB(1.0, 0.921568627451, 0.803921568627);
		const colorRGB blue = colorRGB(0.0, 0.0, 1.0);
		const colorRGB blueviolet = colorRGB(0.541176470588, 0.16862745098, 0.886274509804);
		const colorRGB brown = colorRGB(0.647058823529, 0.164705882353, 0.164705882353);
		const colorRGB burlywood = colorRGB(0.870588235294, 0.721568627451, 0.529411764706);
		const colorRGB cadetblue = colorRGB(0.372549019608, 0.619607843137, 0.627450980392);
		const colorRGB chartreuse = colorRGB(0.498039215686, 1.0, 0.0);
		const colorRGB chocolate = colorRGB(0.823529411765, 0.411764705882, 0.117647058824);
		const colorRGB coral = colorRGB(1.0, 0.498039215686, 0.313725490196);
		const colorRGB cornflowerblue = colorRGB(0.392156862745, 0.58431372549, 0.929411764706);
		const colorRGB cornsilk = colorRGB(1.0, 0.972549019608, 0.862745098039);
		const colorRGB crimson = colorRGB(0.862745098039, 0.078431372549, 0.235294117647);
		const colorRGB cyan = colorRGB(0.0, 1.0, 1.0);
		const colorRGB darkblue = colorRGB(0.0, 0.0, 0.545098039216);
		const colorRGB darkcyan = colorRGB(0.0, 0.545098039216, 0.545098039216);
		const colorRGB darkgoldenrod = colorRGB(0.721568627451, 0.525490196078, 0.043137254902);
		const colorRGB darkgray = colorRGB(0.662745098039, 0.662745098039, 0.662745098039);
		const colorRGB darkgreen = colorRGB(0.0, 0.392156862745, 0.0);
		const colorRGB darkkhaki = colorRGB(0.741176470588, 0.717647058824, 0.419607843137);
		const colorRGB darkmagenta = colorRGB(0.545098039216, 0.0, 0.545098039216);
		const colorRGB darkolivegreen = colorRGB(0.333333333333, 0.419607843137, 0.18431372549);
		const colorRGB darkorange = colorRGB(1.0, 0.549019607843, 0.0);
		const colorRGB darkorchid = colorRGB(0.6, 0.196078431373, 0.8);
		const colorRGB darkred = colorRGB(0.545098039216, 0.0, 0.0);
		const colorRGB darksalmon = colorRGB(0.913725490196, 0.588235294118, 0.478431372549);
		const colorRGB darkseagreen = colorRGB(0.560784313725, 0.737254901961, 0.560784313725);
		const colorRGB darkslateblue = colorRGB(0.282352941176, 0.239215686275, 0.545098039216);
		const colorRGB darkslategray = colorRGB(0.18431372549, 0.309803921569, 0.309803921569);
		const colorRGB darkturquoise = colorRGB(0.0, 0.807843137255, 0.819607843137);
		const colorRGB darkviolet = colorRGB(0.580392156863, 0.0, 0.827450980392);
		const colorRGB deeppink = colorRGB(1.0, 0.078431372549, 0.576470588235);
		const colorRGB deepskyblue = colorRGB(0.0, 0.749019607843, 1.0);
		const colorRGB dimgray = colorRGB(0.411764705882, 0.411764705882, 0.411764705882);
		const colorRGB dodgerblue = colorRGB(0.117647058824, 0.564705882353, 1.0);
		const colorRGB firebrick = colorRGB(0.698039215686, 0.133333333333, 0.133333333333);
		const colorRGB floralwhite = colorRGB(1.0, 0.980392156863, 0.941176470588);
		const colorRGB forestgreen = colorRGB(0.133333333333, 0.545098039216, 0.133333333333);
		const colorRGB fuchsia = colorRGB(1.0, 0.0, 1.0);
		const colorRGB gainsboro = colorRGB(0.862745098039, 0.862745098039, 0.862745098039);
		const colorRGB ghostwhite = colorRGB(0.972549019608, 0.972549019608, 1.0);
		const colorRGB gold = colorRGB(1.0, 0.843137254902, 0.0);
		const colorRGB goldenrod = colorRGB(0.854901960784, 0.647058823529, 0.125490196078);
		const colorRGB gray = colorRGB(0.501960784314, 0.501960784314, 0.501960784314);
		const colorRGB green = colorRGB(0.0, 0.501960784314, 0.0);
		const colorRGB greenyellow = colorRGB(0.678431372549, 1.0, 0.18431372549);
		const colorRGB honeydew = colorRGB(0.941176470588, 1.0, 0.941176470588);
		const colorRGB hotpink = colorRGB(1.0, 0.411764705882, 0.705882352941);
		const colorRGB indianred = colorRGB(0.803921568627, 0.360784313725, 0.360784313725);
		const colorRGB indigo = colorRGB(0.294117647059, 0.0, 0.509803921569);
		const colorRGB ivory = colorRGB(1.0, 1.0, 0.941176470588);
		const colorRGB khaki = colorRGB(0.941176470588, 0.901960784314, 0.549019607843);
		const colorRGB lavender = colorRGB(0.901960784314, 0.901960784314, 0.980392156863);
		const colorRGB lavenderblush = colorRGB(1.0, 0.941176470588, 0.960784313725);
		const colorRGB lawngreen = colorRGB(0.486274509804, 0.988235294118, 0.0);
		const colorRGB lemonchiffon = colorRGB(1.0, 0.980392156863, 0.803921568627);
		const colorRGB lightblue = colorRGB(0.678431372549, 0.847058823529, 0.901960784314);
		const colorRGB lightcoral = colorRGB(0.941176470588, 0.501960784314, 0.501960784314);
		const colorRGB lightcyan = colorRGB(0.878431372549, 1.0, 1.0);
		const colorRGB lightgoldenrodyellow = colorRGB(0.980392156863, 0.980392156863, 0.823529411765);
		const colorRGB lightgray = colorRGB(0.827450980392, 0.827450980392, 0.827450980392);
		const colorRGB lightgreen = colorRGB(0.564705882353, 0.933333333333, 0.564705882353);
		const colorRGB lightpink = colorRGB(1.0, 0.713725490196, 0.756862745098);
		const colorRGB lightsalmon = colorRGB(1.0, 0.627450980392, 0.478431372549);
		const colorRGB lightseagreen = colorRGB(0.125490196078, 0.698039215686, 0.666666666667);
		const colorRGB lightskyblue = colorRGB(0.529411764706, 0.807843137255, 0.980392156863);
		const colorRGB lightslategray = colorRGB(0.466666666667, 0.533333333333, 0.6);
		const colorRGB lightsteelblue = colorRGB(0.690196078431, 0.76862745098, 0.870588235294);
		const colorRGB lightyellow = colorRGB(1.0, 1.0, 0.878431372549);
		const colorRGB lime = colorRGB(0.0, 1.0, 0.0);
		const colorRGB limegreen = colorRGB(0.196078431373, 0.803921568627, 0.196078431373);
		const colorRGB linen = colorRGB(0.980392156863, 0.941176470588, 0.901960784314);
		const colorRGB magenta = colorRGB(1.0, 0.0, 1.0);
		const colorRGB maroon = colorRGB(0.501960784314, 0.0, 0.0);
		const colorRGB mediumaquamarine = colorRGB(0.4, 0.803921568627, 0.666666666667);
		const colorRGB mediumblue = colorRGB(0.0, 0.0, 0.803921568627);
		const colorRGB mediumorchid = colorRGB(0.729411764706, 0.333333333333, 0.827450980392);
		const colorRGB mediumpurple = colorRGB(0.576470588235, 0.439215686275, 0.858823529412);
		const colorRGB mediumseagreen = colorRGB(0.235294117647, 0.701960784314, 0.443137254902);
		const colorRGB mediumslateblue = colorRGB(0.482352941176, 0.407843137255, 0.933333333333);
		const colorRGB mediumspringgreen = colorRGB(0.0, 0.980392156863, 0.603921568627);
		const colorRGB mediumturquoise = colorRGB(0.282352941176, 0.819607843137, 0.8);
		const colorRGB mediumvioletred = colorRGB(0.780392156863, 0.0823529411765, 0.521568627451);
		const colorRGB midnightblue = colorRGB(0.0980392156863, 0.0980392156863, 0.439215686275);
		const colorRGB mintcream = colorRGB(0.960784313725, 1.0, 0.980392156863);
		const colorRGB mistyrose = colorRGB(1.0, 0.894117647059, 0.882352941176);
		const colorRGB moccasin = colorRGB(1.0, 0.894117647059, 0.709803921569);
		const colorRGB navajowhite = colorRGB(1.0, 0.870588235294, 0.678431372549);
		const colorRGB navy = colorRGB(0.0, 0.0, 0.501960784314);
		const colorRGB oldlace = colorRGB(0.992156862745, 0.960784313725, 0.901960784314);
		const colorRGB olive = colorRGB(0.501960784314, 0.501960784314, 0.0);
		const colorRGB olivedrab = colorRGB(0.419607843137, 0.556862745098, 0.137254901961);
		const colorRGB orange = colorRGB(1.0, 0.647058823529, 0.0);
		const colorRGB orangered = colorRGB(1.0, 0.270588235294, 0.0);
		const colorRGB orchid = colorRGB(0.854901960784, 0.439215686275, 0.839215686275);
		const colorRGB palegoldenrod = colorRGB(0.933333333333, 0.909803921569, 0.666666666667);
		const colorRGB palegreen = colorRGB(0.596078431373, 0.98431372549, 0.596078431373);
		const colorRGB paleturquoise = colorRGB(0.686274509804, 0.933333333333, 0.933333333333);
		const colorRGB palevioletred = colorRGB(0.858823529412, 0.439215686275, 0.576470588235);
		const colorRGB papayawhip = colorRGB(1.0, 0.937254901961, 0.835294117647);
		const colorRGB peachpuff = colorRGB(1.0, 0.854901960784, 0.725490196078);
		const colorRGB peru = colorRGB(0.803921568627, 0.521568627451, 0.247058823529);
		const colorRGB pink = colorRGB(1.0, 0.752941176471, 0.796078431373);
		const colorRGB plum = colorRGB(0.866666666667, 0.627450980392, 0.866666666667);
		const colorRGB powderblue = colorRGB(0.690196078431, 0.878431372549, 0.901960784314);
		const colorRGB purple = colorRGB(0.501960784314, 0.0, 0.501960784314);
		const colorRGB red = colorRGB(1.0, 0.0, 0.0);
		const colorRGB rosybrown = colorRGB(0.737254901961, 0.560784313725, 0.560784313725);
		const colorRGB royalblue = colorRGB(0.254901960784, 0.411764705882, 0.882352941176);
		const colorRGB saddlebrown = colorRGB(0.545098039216, 0.270588235294, 0.0745098039216);
		const colorRGB salmon = colorRGB(0.980392156863, 0.501960784314, 0.447058823529);
		const colorRGB sandybrown = colorRGB(0.956862745098, 0.643137254902, 0.376470588235);
		const colorRGB seagreen = colorRGB(0.180392156863, 0.545098039216, 0.341176470588);
		const colorRGB seashell = colorRGB(1.0, 0.960784313725, 0.933333333333);
		const colorRGB sienna = colorRGB(0.627450980392, 0.321568627451, 0.176470588235);
		const colorRGB silver = colorRGB(0.752941176471, 0.752941176471, 0.752941176471);
		const colorRGB skyblue = colorRGB(0.529411764706, 0.807843137255, 0.921568627451);
		const colorRGB slateblue = colorRGB(0.41568627451, 0.352941176471, 0.803921568627);
		const colorRGB slategray = colorRGB(0.439215686275, 0.501960784314, 0.564705882353);
		const colorRGB snow = colorRGB(1.0, 0.980392156863, 0.980392156863);
		const colorRGB springgreen = colorRGB(0.0, 1.0, 0.498039215686);
		const colorRGB steelblue = colorRGB(0.274509803922, 0.509803921569, 0.705882352941);
		const colorRGB tan = colorRGB(0.823529411765, 0.705882352941, 0.549019607843);
		const colorRGB teal = colorRGB(0.0, 0.501960784314, 0.501960784314);
		const colorRGB thistle = colorRGB(0.847058823529, 0.749019607843, 0.847058823529);
		const colorRGB tomato = colorRGB(1.0, 0.388235294118, 0.278431372549);
		const colorRGB turquoise = colorRGB(0.250980392157, 0.878431372549, 0.81568627451);
		const colorRGB violet = colorRGB(0.933333333333, 0.509803921569, 0.933333333333);
		const colorRGB wheat = colorRGB(0.960784313725, 0.870588235294, 0.701960784314);
		const colorRGB white = colorRGB(1.0, 1.0, 1.0);
		const colorRGB whitesmoke = colorRGB(0.960784313725, 0.960784313725, 0.960784313725);
		const colorRGB yellow = colorRGB(1.0, 1.0, 0.0);
		const colorRGB yellowgreen = colorRGB(0.603921568627, 0.803921568627, 0.196078431373);

	}
}

#endif