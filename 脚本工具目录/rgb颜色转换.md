# RGB 常用255色转换

## 需求

使用给 Dear ImGui 定义一批常用颜色。



##　操作

原文：https://vim.fandom.com/wiki/Xterm256_color_names_for_console_Vim

```vim
hi x016_Grey0 ctermfg=16 guifg=#000000 "rgb=0,0,0
hi x017_NavyBlue ctermfg=17 guifg=#00005f "rgb=0,0,95
hi x018_DarkBlue ctermfg=18 guifg=#000087 "rgb=0,0,135
hi x019_Blue3 ctermfg=19 guifg=#0000af "rgb=0,0,175
hi x020_Blue3 ctermfg=20 guifg=#0000d7 "rgb=0,0,215
hi x021_Blue1 ctermfg=21 guifg=#0000ff "rgb=0,0,255
hi x022_DarkGreen ctermfg=22 guifg=#005f00 "rgb=0,95,0
hi x023_DeepSkyBlue4 ctermfg=23 guifg=#005f5f "rgb=0,95,95
hi x024_DeepSkyBlue4 ctermfg=24 guifg=#005f87 "rgb=0,95,135
hi x025_DeepSkyBlue4 ctermfg=25 guifg=#005faf "rgb=0,95,175
hi x026_DodgerBlue3 ctermfg=26 guifg=#005fd7 "rgb=0,95,215
hi x027_DodgerBlue2 ctermfg=27 guifg=#005fff "rgb=0,95,255
hi x028_Green4 ctermfg=28 guifg=#008700 "rgb=0,135,0
hi x029_SpringGreen4 ctermfg=29 guifg=#00875f "rgb=0,135,95
hi x030_Turquoise4 ctermfg=30 guifg=#008787 "rgb=0,135,135
hi x031_DeepSkyBlue3 ctermfg=31 guifg=#0087af "rgb=0,135,175
hi x032_DeepSkyBlue3 ctermfg=32 guifg=#0087d7 "rgb=0,135,215
hi x033_DodgerBlue1 ctermfg=33 guifg=#0087ff "rgb=0,135,255
hi x034_Green3 ctermfg=34 guifg=#00af00 "rgb=0,175,0
hi x035_SpringGreen3 ctermfg=35 guifg=#00af5f "rgb=0,175,95
hi x036_DarkCyan ctermfg=36 guifg=#00af87 "rgb=0,175,135
hi x037_LightSeaGreen ctermfg=37 guifg=#00afaf "rgb=0,175,175
hi x038_DeepSkyBlue2 ctermfg=38 guifg=#00afd7 "rgb=0,175,215
hi x039_DeepSkyBlue1 ctermfg=39 guifg=#00afff "rgb=0,175,255
hi x040_Green3 ctermfg=40 guifg=#00d700 "rgb=0,215,0
hi x041_SpringGreen3 ctermfg=41 guifg=#00d75f "rgb=0,215,95
hi x042_SpringGreen2 ctermfg=42 guifg=#00d787 "rgb=0,215,135
hi x043_Cyan3 ctermfg=43 guifg=#00d7af "rgb=0,215,175
hi x044_DarkTurquoise ctermfg=44 guifg=#00d7d7 "rgb=0,215,215
hi x045_Turquoise2 ctermfg=45 guifg=#00d7ff "rgb=0,215,255
hi x046_Green1 ctermfg=46 guifg=#00ff00 "rgb=0,255,0
hi x047_SpringGreen2 ctermfg=47 guifg=#00ff5f "rgb=0,255,95
hi x048_SpringGreen1 ctermfg=48 guifg=#00ff87 "rgb=0,255,135
hi x049_MediumSpringGreen ctermfg=49 guifg=#00ffaf "rgb=0,255,175
hi x050_Cyan2 ctermfg=50 guifg=#00ffd7 "rgb=0,255,215
hi x051_Cyan1 ctermfg=51 guifg=#00ffff "rgb=0,255,255
hi x052_DarkRed ctermfg=52 guifg=#5f0000 "rgb=95,0,0
hi x053_DeepPink4 ctermfg=53 guifg=#5f005f "rgb=95,0,95
hi x054_Purple4 ctermfg=54 guifg=#5f0087 "rgb=95,0,135
hi x055_Purple4 ctermfg=55 guifg=#5f00af "rgb=95,0,175
hi x056_Purple3 ctermfg=56 guifg=#5f00d7 "rgb=95,0,215
hi x057_BlueViolet ctermfg=57 guifg=#5f00ff "rgb=95,0,255
hi x058_Orange4 ctermfg=58 guifg=#5f5f00 "rgb=95,95,0
hi x059_Grey37 ctermfg=59 guifg=#5f5f5f "rgb=95,95,95
hi x060_MediumPurple4 ctermfg=60 guifg=#5f5f87 "rgb=95,95,135
hi x061_SlateBlue3 ctermfg=61 guifg=#5f5faf "rgb=95,95,175
hi x062_SlateBlue3 ctermfg=62 guifg=#5f5fd7 "rgb=95,95,215
hi x063_RoyalBlue1 ctermfg=63 guifg=#5f5fff "rgb=95,95,255
hi x064_Chartreuse4 ctermfg=64 guifg=#5f8700 "rgb=95,135,0
hi x065_DarkSeaGreen4 ctermfg=65 guifg=#5f875f "rgb=95,135,95
hi x066_PaleTurquoise4 ctermfg=66 guifg=#5f8787 "rgb=95,135,135
hi x067_SteelBlue ctermfg=67 guifg=#5f87af "rgb=95,135,175
hi x068_SteelBlue3 ctermfg=68 guifg=#5f87d7 "rgb=95,135,215
hi x069_CornflowerBlue ctermfg=69 guifg=#5f87ff "rgb=95,135,255
hi x070_Chartreuse3 ctermfg=70 guifg=#5faf00 "rgb=95,175,0
hi x071_DarkSeaGreen4 ctermfg=71 guifg=#5faf5f "rgb=95,175,95
hi x072_CadetBlue ctermfg=72 guifg=#5faf87 "rgb=95,175,135
hi x073_CadetBlue ctermfg=73 guifg=#5fafaf "rgb=95,175,175
hi x074_SkyBlue3 ctermfg=74 guifg=#5fafd7 "rgb=95,175,215
hi x075_SteelBlue1 ctermfg=75 guifg=#5fafff "rgb=95,175,255
hi x076_Chartreuse3 ctermfg=76 guifg=#5fd700 "rgb=95,215,0
hi x077_PaleGreen3 ctermfg=77 guifg=#5fd75f "rgb=95,215,95
hi x078_SeaGreen3 ctermfg=78 guifg=#5fd787 "rgb=95,215,135
hi x079_Aquamarine3 ctermfg=79 guifg=#5fd7af "rgb=95,215,175
hi x080_MediumTurquoise ctermfg=80 guifg=#5fd7d7 "rgb=95,215,215
hi x081_SteelBlue1 ctermfg=81 guifg=#5fd7ff "rgb=95,215,255
hi x082_Chartreuse2 ctermfg=82 guifg=#5fff00 "rgb=95,255,0
hi x083_SeaGreen2 ctermfg=83 guifg=#5fff5f "rgb=95,255,95
hi x084_SeaGreen1 ctermfg=84 guifg=#5fff87 "rgb=95,255,135
hi x085_SeaGreen1 ctermfg=85 guifg=#5fffaf "rgb=95,255,175
hi x086_Aquamarine1 ctermfg=86 guifg=#5fffd7 "rgb=95,255,215
hi x087_DarkSlateGray2 ctermfg=87 guifg=#5fffff "rgb=95,255,255
hi x088_DarkRed ctermfg=88 guifg=#870000 "rgb=135,0,0
hi x089_DeepPink4 ctermfg=89 guifg=#87005f "rgb=135,0,95
hi x090_DarkMagenta ctermfg=90 guifg=#870087 "rgb=135,0,135
hi x091_DarkMagenta ctermfg=91 guifg=#8700af "rgb=135,0,175
hi x092_DarkViolet ctermfg=92 guifg=#8700d7 "rgb=135,0,215
hi x093_Purple ctermfg=93 guifg=#8700ff "rgb=135,0,255
hi x094_Orange4 ctermfg=94 guifg=#875f00 "rgb=135,95,0
hi x095_LightPink4 ctermfg=95 guifg=#875f5f "rgb=135,95,95
hi x096_Plum4 ctermfg=96 guifg=#875f87 "rgb=135,95,135
hi x097_MediumPurple3 ctermfg=97 guifg=#875faf "rgb=135,95,175
hi x098_MediumPurple3 ctermfg=98 guifg=#875fd7 "rgb=135,95,215
hi x099_SlateBlue1 ctermfg=99 guifg=#875fff "rgb=135,95,255
hi x100_Yellow4 ctermfg=100 guifg=#878700 "rgb=135,135,0
hi x101_Wheat4 ctermfg=101 guifg=#87875f "rgb=135,135,95
hi x102_Grey53 ctermfg=102 guifg=#878787 "rgb=135,135,135
hi x103_LightSlateGrey ctermfg=103 guifg=#8787af "rgb=135,135,175
hi x104_MediumPurple ctermfg=104 guifg=#8787d7 "rgb=135,135,215
hi x105_LightSlateBlue ctermfg=105 guifg=#8787ff "rgb=135,135,255
hi x106_Yellow4 ctermfg=106 guifg=#87af00 "rgb=135,175,0
hi x107_DarkOliveGreen3 ctermfg=107 guifg=#87af5f "rgb=135,175,95
hi x108_DarkSeaGreen ctermfg=108 guifg=#87af87 "rgb=135,175,135
hi x109_LightSkyBlue3 ctermfg=109 guifg=#87afaf "rgb=135,175,175
hi x110_LightSkyBlue3 ctermfg=110 guifg=#87afd7 "rgb=135,175,215
hi x111_SkyBlue2 ctermfg=111 guifg=#87afff "rgb=135,175,255
hi x112_Chartreuse2 ctermfg=112 guifg=#87d700 "rgb=135,215,0
hi x113_DarkOliveGreen3 ctermfg=113 guifg=#87d75f "rgb=135,215,95
hi x114_PaleGreen3 ctermfg=114 guifg=#87d787 "rgb=135,215,135
hi x115_DarkSeaGreen3 ctermfg=115 guifg=#87d7af "rgb=135,215,175
hi x116_DarkSlateGray3 ctermfg=116 guifg=#87d7d7 "rgb=135,215,215
hi x117_SkyBlue1 ctermfg=117 guifg=#87d7ff "rgb=135,215,255
hi x118_Chartreuse1 ctermfg=118 guifg=#87ff00 "rgb=135,255,0
hi x119_LightGreen ctermfg=119 guifg=#87ff5f "rgb=135,255,95
hi x120_LightGreen ctermfg=120 guifg=#87ff87 "rgb=135,255,135
hi x121_PaleGreen1 ctermfg=121 guifg=#87ffaf "rgb=135,255,175
hi x122_Aquamarine1 ctermfg=122 guifg=#87ffd7 "rgb=135,255,215
hi x123_DarkSlateGray1 ctermfg=123 guifg=#87ffff "rgb=135,255,255
hi x124_Red3 ctermfg=124 guifg=#af0000 "rgb=175,0,0
hi x125_DeepPink4 ctermfg=125 guifg=#af005f "rgb=175,0,95
hi x126_MediumVioletRed ctermfg=126 guifg=#af0087 "rgb=175,0,135
hi x127_Magenta3 ctermfg=127 guifg=#af00af "rgb=175,0,175
hi x128_DarkViolet ctermfg=128 guifg=#af00d7 "rgb=175,0,215
hi x129_Purple ctermfg=129 guifg=#af00ff "rgb=175,0,255
hi x130_DarkOrange3 ctermfg=130 guifg=#af5f00 "rgb=175,95,0
hi x131_IndianRed ctermfg=131 guifg=#af5f5f "rgb=175,95,95
hi x132_HotPink3 ctermfg=132 guifg=#af5f87 "rgb=175,95,135
hi x133_MediumOrchid3 ctermfg=133 guifg=#af5faf "rgb=175,95,175
hi x134_MediumOrchid ctermfg=134 guifg=#af5fd7 "rgb=175,95,215
hi x135_MediumPurple2 ctermfg=135 guifg=#af5fff "rgb=175,95,255
hi x136_DarkGoldenrod ctermfg=136 guifg=#af8700 "rgb=175,135,0
hi x137_LightSalmon3 ctermfg=137 guifg=#af875f "rgb=175,135,95
hi x138_RosyBrown ctermfg=138 guifg=#af8787 "rgb=175,135,135
hi x139_Grey63 ctermfg=139 guifg=#af87af "rgb=175,135,175
hi x140_MediumPurple2 ctermfg=140 guifg=#af87d7 "rgb=175,135,215
hi x141_MediumPurple1 ctermfg=141 guifg=#af87ff "rgb=175,135,255
hi x142_Gold3 ctermfg=142 guifg=#afaf00 "rgb=175,175,0
hi x143_DarkKhaki ctermfg=143 guifg=#afaf5f "rgb=175,175,95
hi x144_NavajoWhite3 ctermfg=144 guifg=#afaf87 "rgb=175,175,135
hi x145_Grey69 ctermfg=145 guifg=#afafaf "rgb=175,175,175
hi x146_LightSteelBlue3 ctermfg=146 guifg=#afafd7 "rgb=175,175,215
hi x147_LightSteelBlue ctermfg=147 guifg=#afafff "rgb=175,175,255
hi x148_Yellow3 ctermfg=148 guifg=#afd700 "rgb=175,215,0
hi x149_DarkOliveGreen3 ctermfg=149 guifg=#afd75f "rgb=175,215,95
hi x150_DarkSeaGreen3 ctermfg=150 guifg=#afd787 "rgb=175,215,135
hi x151_DarkSeaGreen2 ctermfg=151 guifg=#afd7af "rgb=175,215,175
hi x152_LightCyan3 ctermfg=152 guifg=#afd7d7 "rgb=175,215,215
hi x153_LightSkyBlue1 ctermfg=153 guifg=#afd7ff "rgb=175,215,255
hi x154_GreenYellow ctermfg=154 guifg=#afff00 "rgb=175,255,0
hi x155_DarkOliveGreen2 ctermfg=155 guifg=#afff5f "rgb=175,255,95
hi x156_PaleGreen1 ctermfg=156 guifg=#afff87 "rgb=175,255,135
hi x157_DarkSeaGreen2 ctermfg=157 guifg=#afffaf "rgb=175,255,175
hi x158_DarkSeaGreen1 ctermfg=158 guifg=#afffd7 "rgb=175,255,215
hi x159_PaleTurquoise1 ctermfg=159 guifg=#afffff "rgb=175,255,255
hi x160_Red3 ctermfg=160 guifg=#d70000 "rgb=215,0,0
hi x161_DeepPink3 ctermfg=161 guifg=#d7005f "rgb=215,0,95
hi x162_DeepPink3 ctermfg=162 guifg=#d70087 "rgb=215,0,135
hi x163_Magenta3 ctermfg=163 guifg=#d700af "rgb=215,0,175
hi x164_Magenta3 ctermfg=164 guifg=#d700d7 "rgb=215,0,215
hi x165_Magenta2 ctermfg=165 guifg=#d700ff "rgb=215,0,255
hi x166_DarkOrange3 ctermfg=166 guifg=#d75f00 "rgb=215,95,0
hi x167_IndianRed ctermfg=167 guifg=#d75f5f "rgb=215,95,95
hi x168_HotPink3 ctermfg=168 guifg=#d75f87 "rgb=215,95,135
hi x169_HotPink2 ctermfg=169 guifg=#d75faf "rgb=215,95,175
hi x170_Orchid ctermfg=170 guifg=#d75fd7 "rgb=215,95,215
hi x171_MediumOrchid1 ctermfg=171 guifg=#d75fff "rgb=215,95,255
hi x172_Orange3 ctermfg=172 guifg=#d78700 "rgb=215,135,0
hi x173_LightSalmon3 ctermfg=173 guifg=#d7875f "rgb=215,135,95
hi x174_LightPink3 ctermfg=174 guifg=#d78787 "rgb=215,135,135
hi x175_Pink3 ctermfg=175 guifg=#d787af "rgb=215,135,175
hi x176_Plum3 ctermfg=176 guifg=#d787d7 "rgb=215,135,215
hi x177_Violet ctermfg=177 guifg=#d787ff "rgb=215,135,255
hi x178_Gold3 ctermfg=178 guifg=#d7af00 "rgb=215,175,0
hi x179_LightGoldenrod3 ctermfg=179 guifg=#d7af5f "rgb=215,175,95
hi x180_Tan ctermfg=180 guifg=#d7af87 "rgb=215,175,135
hi x181_MistyRose3 ctermfg=181 guifg=#d7afaf "rgb=215,175,175
hi x182_Thistle3 ctermfg=182 guifg=#d7afd7 "rgb=215,175,215
hi x183_Plum2 ctermfg=183 guifg=#d7afff "rgb=215,175,255
hi x184_Yellow3 ctermfg=184 guifg=#d7d700 "rgb=215,215,0
hi x185_Khaki3 ctermfg=185 guifg=#d7d75f "rgb=215,215,95
hi x186_LightGoldenrod2 ctermfg=186 guifg=#d7d787 "rgb=215,215,135
hi x187_LightYellow3 ctermfg=187 guifg=#d7d7af "rgb=215,215,175
hi x188_Grey84 ctermfg=188 guifg=#d7d7d7 "rgb=215,215,215
hi x189_LightSteelBlue1 ctermfg=189 guifg=#d7d7ff "rgb=215,215,255
hi x190_Yellow2 ctermfg=190 guifg=#d7ff00 "rgb=215,255,0
hi x191_DarkOliveGreen1 ctermfg=191 guifg=#d7ff5f "rgb=215,255,95
hi x192_DarkOliveGreen1 ctermfg=192 guifg=#d7ff87 "rgb=215,255,135
hi x193_DarkSeaGreen1 ctermfg=193 guifg=#d7ffaf "rgb=215,255,175
hi x194_Honeydew2 ctermfg=194 guifg=#d7ffd7 "rgb=215,255,215
hi x195_LightCyan1 ctermfg=195 guifg=#d7ffff "rgb=215,255,255
hi x196_Red1 ctermfg=196 guifg=#ff0000 "rgb=255,0,0
hi x197_DeepPink2 ctermfg=197 guifg=#ff005f "rgb=255,0,95
hi x198_DeepPink1 ctermfg=198 guifg=#ff0087 "rgb=255,0,135
hi x199_DeepPink1 ctermfg=199 guifg=#ff00af "rgb=255,0,175
hi x200_Magenta2 ctermfg=200 guifg=#ff00d7 "rgb=255,0,215
hi x201_Magenta1 ctermfg=201 guifg=#ff00ff "rgb=255,0,255
hi x202_OrangeRed1 ctermfg=202 guifg=#ff5f00 "rgb=255,95,0
hi x203_IndianRed1 ctermfg=203 guifg=#ff5f5f "rgb=255,95,95
hi x204_IndianRed1 ctermfg=204 guifg=#ff5f87 "rgb=255,95,135
hi x205_HotPink ctermfg=205 guifg=#ff5faf "rgb=255,95,175
hi x206_HotPink ctermfg=206 guifg=#ff5fd7 "rgb=255,95,215
hi x207_MediumOrchid1 ctermfg=207 guifg=#ff5fff "rgb=255,95,255
hi x208_DarkOrange ctermfg=208 guifg=#ff8700 "rgb=255,135,0
hi x209_Salmon1 ctermfg=209 guifg=#ff875f "rgb=255,135,95
hi x210_LightCoral ctermfg=210 guifg=#ff8787 "rgb=255,135,135
hi x211_PaleVioletRed1 ctermfg=211 guifg=#ff87af "rgb=255,135,175
hi x212_Orchid2 ctermfg=212 guifg=#ff87d7 "rgb=255,135,215
hi x213_Orchid1 ctermfg=213 guifg=#ff87ff "rgb=255,135,255
hi x214_Orange1 ctermfg=214 guifg=#ffaf00 "rgb=255,175,0
hi x215_SandyBrown ctermfg=215 guifg=#ffaf5f "rgb=255,175,95
hi x216_LightSalmon1 ctermfg=216 guifg=#ffaf87 "rgb=255,175,135
hi x217_LightPink1 ctermfg=217 guifg=#ffafaf "rgb=255,175,175
hi x218_Pink1 ctermfg=218 guifg=#ffafd7 "rgb=255,175,215
hi x219_Plum1 ctermfg=219 guifg=#ffafff "rgb=255,175,255
hi x220_Gold1 ctermfg=220 guifg=#ffd700 "rgb=255,215,0
hi x221_LightGoldenrod2 ctermfg=221 guifg=#ffd75f "rgb=255,215,95
hi x222_LightGoldenrod2 ctermfg=222 guifg=#ffd787 "rgb=255,215,135
hi x223_NavajoWhite1 ctermfg=223 guifg=#ffd7af "rgb=255,215,175
hi x224_MistyRose1 ctermfg=224 guifg=#ffd7d7 "rgb=255,215,215
hi x225_Thistle1 ctermfg=225 guifg=#ffd7ff "rgb=255,215,255
hi x226_Yellow1 ctermfg=226 guifg=#ffff00 "rgb=255,255,0
hi x227_LightGoldenrod1 ctermfg=227 guifg=#ffff5f "rgb=255,255,95
hi x228_Khaki1 ctermfg=228 guifg=#ffff87 "rgb=255,255,135
hi x229_Wheat1 ctermfg=229 guifg=#ffffaf "rgb=255,255,175
hi x230_Cornsilk1 ctermfg=230 guifg=#ffffd7 "rgb=255,255,215
hi x231_Grey100 ctermfg=231 guifg=#ffffff "rgb=255,255,255
hi x232_Grey3 ctermfg=232 guifg=#080808 "rgb=8,8,8
hi x233_Grey7 ctermfg=233 guifg=#121212 "rgb=18,18,18
hi x234_Grey11 ctermfg=234 guifg=#1c1c1c "rgb=28,28,28
hi x235_Grey15 ctermfg=235 guifg=#262626 "rgb=38,38,38
hi x236_Grey19 ctermfg=236 guifg=#303030 "rgb=48,48,48
hi x237_Grey23 ctermfg=237 guifg=#3a3a3a "rgb=58,58,58
hi x238_Grey27 ctermfg=238 guifg=#444444 "rgb=68,68,68
hi x239_Grey30 ctermfg=239 guifg=#4e4e4e "rgb=78,78,78
hi x240_Grey35 ctermfg=240 guifg=#585858 "rgb=88,88,88
hi x241_Grey39 ctermfg=241 guifg=#626262 "rgb=98,98,98
hi x242_Grey42 ctermfg=242 guifg=#6c6c6c "rgb=108,108,108
hi x243_Grey46 ctermfg=243 guifg=#767676 "rgb=118,118,118
hi x244_Grey50 ctermfg=244 guifg=#808080 "rgb=128,128,128
hi x245_Grey54 ctermfg=245 guifg=#8a8a8a "rgb=138,138,138
hi x246_Grey58 ctermfg=246 guifg=#949494 "rgb=148,148,148
hi x247_Grey62 ctermfg=247 guifg=#9e9e9e "rgb=158,158,158
hi x248_Grey66 ctermfg=248 guifg=#a8a8a8 "rgb=168,168,168
hi x249_Grey70 ctermfg=249 guifg=#b2b2b2 "rgb=178,178,178
hi x250_Grey74 ctermfg=250 guifg=#bcbcbc "rgb=188,188,188
hi x251_Grey78 ctermfg=251 guifg=#c6c6c6 "rgb=198,198,198
hi x252_Grey82 ctermfg=252 guifg=#d0d0d0 "rgb=208,208,208
hi x253_Grey85 ctermfg=253 guifg=#dadada "rgb=218,218,218
hi x254_Grey89 ctermfg=254 guifg=#e4e4e4 "rgb=228,228,228
hi x255_Grey93 ctermfg=255 guifg=#eeeeee "rgb=238,238,238
```



使用 awk 切出第二列和第五列

```bash
awk '{print $2,$5}' 256color.txt > 256color2.txt
```

使用 python 脚本做归一化

```python
m = set()

def normalize(n: float) -> float:
    return round(n / 255, 2)

def processLine(line: str) -> str:
    color = line.split()[0].split("_")[1]
    # 有些颜色名字相同，去重
    if color in m:
        return
    else:
        m.add(color)

    rgb = line.split()[1].split("=")[1]

    r = rgb.split(",")[0]
    g = rgb.split(",")[1]
    b = rgb.split(",")[2]

    # 归一化
    rf = normalize(float(r))
    gf = normalize(float(g))
    bf = normalize(float(b))

    # 格式化
    line = "#define RLVColor_{}_Alpha0 ImVec4{{ {},{},{}, 0.0 }}".format(color, rf, gf, bf)
    print(line)
    
    line = "#define RLVColor_{}_Alpha1 ImVec4{{ {},{},{}, 0.2 }}".format(color, rf, gf, bf)
    print(line)

    line = "#define RLVColor_{}_Alpha2 ImVec4{{ {},{},{}, 0.4 }}".format(color, rf, gf, bf)
    print(line)

    line = "#define RLVColor_{}_Alpha3 ImVec4{{ {},{},{}, 0.6 }}".format(color, rf, gf, bf)
    print(line)

    line = "#define RLVColor_{}_Alpha4 ImVec4{{ {},{},{}, 0.8 }}".format(color, rf, gf, bf)
    print(line)

    line = "#define RLVColor_{}_Alpha5 ImVec4{{ {},{},{}, 1.0 }}".format(color, rf, gf, bf)
    print(line)
    print()

if __name__ == "__main__":
    print("#pragma once")
    print("#include \"3rd/imgui/imgui.h\"")
    print()
    
    with open("256color2.txt") as f:
        while True:
            line = f.readline()
            if not line:
                break
            processLine(f.readline())
```



## 处理结果

```c++
#pragma once
#include "3rd/imgui/imgui.h"

#define RLVColor_NavyBlue_Alpha0 ImVec4{ 0.0,0.0,0.37, 0.0 }
#define RLVColor_NavyBlue_Alpha1 ImVec4{ 0.0,0.0,0.37, 0.2 }
#define RLVColor_NavyBlue_Alpha2 ImVec4{ 0.0,0.0,0.37, 0.4 }
#define RLVColor_NavyBlue_Alpha3 ImVec4{ 0.0,0.0,0.37, 0.6 }
#define RLVColor_NavyBlue_Alpha4 ImVec4{ 0.0,0.0,0.37, 0.8 }
#define RLVColor_NavyBlue_Alpha5 ImVec4{ 0.0,0.0,0.37, 1.0 }

#define RLVColor_Blue3_Alpha0 ImVec4{ 0.0,0.0,0.69, 0.0 }
#define RLVColor_Blue3_Alpha1 ImVec4{ 0.0,0.0,0.69, 0.2 }
#define RLVColor_Blue3_Alpha2 ImVec4{ 0.0,0.0,0.69, 0.4 }
#define RLVColor_Blue3_Alpha3 ImVec4{ 0.0,0.0,0.69, 0.6 }
#define RLVColor_Blue3_Alpha4 ImVec4{ 0.0,0.0,0.69, 0.8 }
#define RLVColor_Blue3_Alpha5 ImVec4{ 0.0,0.0,0.69, 1.0 }

#define RLVColor_Blue1_Alpha0 ImVec4{ 0.0,0.0,1.0, 0.0 }
#define RLVColor_Blue1_Alpha1 ImVec4{ 0.0,0.0,1.0, 0.2 }
#define RLVColor_Blue1_Alpha2 ImVec4{ 0.0,0.0,1.0, 0.4 }
#define RLVColor_Blue1_Alpha3 ImVec4{ 0.0,0.0,1.0, 0.6 }
#define RLVColor_Blue1_Alpha4 ImVec4{ 0.0,0.0,1.0, 0.8 }
#define RLVColor_Blue1_Alpha5 ImVec4{ 0.0,0.0,1.0, 1.0 }

#define RLVColor_DeepSkyBlue4_Alpha0 ImVec4{ 0.0,0.37,0.37, 0.0 }
#define RLVColor_DeepSkyBlue4_Alpha1 ImVec4{ 0.0,0.37,0.37, 0.2 }
#define RLVColor_DeepSkyBlue4_Alpha2 ImVec4{ 0.0,0.37,0.37, 0.4 }
#define RLVColor_DeepSkyBlue4_Alpha3 ImVec4{ 0.0,0.37,0.37, 0.6 }
#define RLVColor_DeepSkyBlue4_Alpha4 ImVec4{ 0.0,0.37,0.37, 0.8 }
#define RLVColor_DeepSkyBlue4_Alpha5 ImVec4{ 0.0,0.37,0.37, 1.0 }

#define RLVColor_DodgerBlue2_Alpha0 ImVec4{ 0.0,0.37,1.0, 0.0 }
#define RLVColor_DodgerBlue2_Alpha1 ImVec4{ 0.0,0.37,1.0, 0.2 }
#define RLVColor_DodgerBlue2_Alpha2 ImVec4{ 0.0,0.37,1.0, 0.4 }
#define RLVColor_DodgerBlue2_Alpha3 ImVec4{ 0.0,0.37,1.0, 0.6 }
#define RLVColor_DodgerBlue2_Alpha4 ImVec4{ 0.0,0.37,1.0, 0.8 }
#define RLVColor_DodgerBlue2_Alpha5 ImVec4{ 0.0,0.37,1.0, 1.0 }

#define RLVColor_SpringGreen4_Alpha0 ImVec4{ 0.0,0.53,0.37, 0.0 }
#define RLVColor_SpringGreen4_Alpha1 ImVec4{ 0.0,0.53,0.37, 0.2 }
#define RLVColor_SpringGreen4_Alpha2 ImVec4{ 0.0,0.53,0.37, 0.4 }
#define RLVColor_SpringGreen4_Alpha3 ImVec4{ 0.0,0.53,0.37, 0.6 }
#define RLVColor_SpringGreen4_Alpha4 ImVec4{ 0.0,0.53,0.37, 0.8 }
#define RLVColor_SpringGreen4_Alpha5 ImVec4{ 0.0,0.53,0.37, 1.0 }

#define RLVColor_DeepSkyBlue3_Alpha0 ImVec4{ 0.0,0.53,0.69, 0.0 }
#define RLVColor_DeepSkyBlue3_Alpha1 ImVec4{ 0.0,0.53,0.69, 0.2 }
#define RLVColor_DeepSkyBlue3_Alpha2 ImVec4{ 0.0,0.53,0.69, 0.4 }
#define RLVColor_DeepSkyBlue3_Alpha3 ImVec4{ 0.0,0.53,0.69, 0.6 }
#define RLVColor_DeepSkyBlue3_Alpha4 ImVec4{ 0.0,0.53,0.69, 0.8 }
#define RLVColor_DeepSkyBlue3_Alpha5 ImVec4{ 0.0,0.53,0.69, 1.0 }

#define RLVColor_DodgerBlue1_Alpha0 ImVec4{ 0.0,0.53,1.0, 0.0 }
#define RLVColor_DodgerBlue1_Alpha1 ImVec4{ 0.0,0.53,1.0, 0.2 }
#define RLVColor_DodgerBlue1_Alpha2 ImVec4{ 0.0,0.53,1.0, 0.4 }
#define RLVColor_DodgerBlue1_Alpha3 ImVec4{ 0.0,0.53,1.0, 0.6 }
#define RLVColor_DodgerBlue1_Alpha4 ImVec4{ 0.0,0.53,1.0, 0.8 }
#define RLVColor_DodgerBlue1_Alpha5 ImVec4{ 0.0,0.53,1.0, 1.0 }

#define RLVColor_SpringGreen3_Alpha0 ImVec4{ 0.0,0.69,0.37, 0.0 }
#define RLVColor_SpringGreen3_Alpha1 ImVec4{ 0.0,0.69,0.37, 0.2 }
#define RLVColor_SpringGreen3_Alpha2 ImVec4{ 0.0,0.69,0.37, 0.4 }
#define RLVColor_SpringGreen3_Alpha3 ImVec4{ 0.0,0.69,0.37, 0.6 }
#define RLVColor_SpringGreen3_Alpha4 ImVec4{ 0.0,0.69,0.37, 0.8 }
#define RLVColor_SpringGreen3_Alpha5 ImVec4{ 0.0,0.69,0.37, 1.0 }

#define RLVColor_LightSeaGreen_Alpha0 ImVec4{ 0.0,0.69,0.69, 0.0 }
#define RLVColor_LightSeaGreen_Alpha1 ImVec4{ 0.0,0.69,0.69, 0.2 }
#define RLVColor_LightSeaGreen_Alpha2 ImVec4{ 0.0,0.69,0.69, 0.4 }
#define RLVColor_LightSeaGreen_Alpha3 ImVec4{ 0.0,0.69,0.69, 0.6 }
#define RLVColor_LightSeaGreen_Alpha4 ImVec4{ 0.0,0.69,0.69, 0.8 }
#define RLVColor_LightSeaGreen_Alpha5 ImVec4{ 0.0,0.69,0.69, 1.0 }

#define RLVColor_DeepSkyBlue1_Alpha0 ImVec4{ 0.0,0.69,1.0, 0.0 }
#define RLVColor_DeepSkyBlue1_Alpha1 ImVec4{ 0.0,0.69,1.0, 0.2 }
#define RLVColor_DeepSkyBlue1_Alpha2 ImVec4{ 0.0,0.69,1.0, 0.4 }
#define RLVColor_DeepSkyBlue1_Alpha3 ImVec4{ 0.0,0.69,1.0, 0.6 }
#define RLVColor_DeepSkyBlue1_Alpha4 ImVec4{ 0.0,0.69,1.0, 0.8 }
#define RLVColor_DeepSkyBlue1_Alpha5 ImVec4{ 0.0,0.69,1.0, 1.0 }

#define RLVColor_Cyan3_Alpha0 ImVec4{ 0.0,0.84,0.69, 0.0 }
#define RLVColor_Cyan3_Alpha1 ImVec4{ 0.0,0.84,0.69, 0.2 }
#define RLVColor_Cyan3_Alpha2 ImVec4{ 0.0,0.84,0.69, 0.4 }
#define RLVColor_Cyan3_Alpha3 ImVec4{ 0.0,0.84,0.69, 0.6 }
#define RLVColor_Cyan3_Alpha4 ImVec4{ 0.0,0.84,0.69, 0.8 }
#define RLVColor_Cyan3_Alpha5 ImVec4{ 0.0,0.84,0.69, 1.0 }

#define RLVColor_Turquoise2_Alpha0 ImVec4{ 0.0,0.84,1.0, 0.0 }
#define RLVColor_Turquoise2_Alpha1 ImVec4{ 0.0,0.84,1.0, 0.2 }
#define RLVColor_Turquoise2_Alpha2 ImVec4{ 0.0,0.84,1.0, 0.4 }
#define RLVColor_Turquoise2_Alpha3 ImVec4{ 0.0,0.84,1.0, 0.6 }
#define RLVColor_Turquoise2_Alpha4 ImVec4{ 0.0,0.84,1.0, 0.8 }
#define RLVColor_Turquoise2_Alpha5 ImVec4{ 0.0,0.84,1.0, 1.0 }

#define RLVColor_SpringGreen2_Alpha0 ImVec4{ 0.0,1.0,0.37, 0.0 }
#define RLVColor_SpringGreen2_Alpha1 ImVec4{ 0.0,1.0,0.37, 0.2 }
#define RLVColor_SpringGreen2_Alpha2 ImVec4{ 0.0,1.0,0.37, 0.4 }
#define RLVColor_SpringGreen2_Alpha3 ImVec4{ 0.0,1.0,0.37, 0.6 }
#define RLVColor_SpringGreen2_Alpha4 ImVec4{ 0.0,1.0,0.37, 0.8 }
#define RLVColor_SpringGreen2_Alpha5 ImVec4{ 0.0,1.0,0.37, 1.0 }

#define RLVColor_MediumSpringGreen_Alpha0 ImVec4{ 0.0,1.0,0.69, 0.0 }
#define RLVColor_MediumSpringGreen_Alpha1 ImVec4{ 0.0,1.0,0.69, 0.2 }
#define RLVColor_MediumSpringGreen_Alpha2 ImVec4{ 0.0,1.0,0.69, 0.4 }
#define RLVColor_MediumSpringGreen_Alpha3 ImVec4{ 0.0,1.0,0.69, 0.6 }
#define RLVColor_MediumSpringGreen_Alpha4 ImVec4{ 0.0,1.0,0.69, 0.8 }
#define RLVColor_MediumSpringGreen_Alpha5 ImVec4{ 0.0,1.0,0.69, 1.0 }

#define RLVColor_Cyan1_Alpha0 ImVec4{ 0.0,1.0,1.0, 0.0 }
#define RLVColor_Cyan1_Alpha1 ImVec4{ 0.0,1.0,1.0, 0.2 }
#define RLVColor_Cyan1_Alpha2 ImVec4{ 0.0,1.0,1.0, 0.4 }
#define RLVColor_Cyan1_Alpha3 ImVec4{ 0.0,1.0,1.0, 0.6 }
#define RLVColor_Cyan1_Alpha4 ImVec4{ 0.0,1.0,1.0, 0.8 }
#define RLVColor_Cyan1_Alpha5 ImVec4{ 0.0,1.0,1.0, 1.0 }

#define RLVColor_DeepPink4_Alpha0 ImVec4{ 0.37,0.0,0.37, 0.0 }
#define RLVColor_DeepPink4_Alpha1 ImVec4{ 0.37,0.0,0.37, 0.2 }
#define RLVColor_DeepPink4_Alpha2 ImVec4{ 0.37,0.0,0.37, 0.4 }
#define RLVColor_DeepPink4_Alpha3 ImVec4{ 0.37,0.0,0.37, 0.6 }
#define RLVColor_DeepPink4_Alpha4 ImVec4{ 0.37,0.0,0.37, 0.8 }
#define RLVColor_DeepPink4_Alpha5 ImVec4{ 0.37,0.0,0.37, 1.0 }

#define RLVColor_Purple4_Alpha0 ImVec4{ 0.37,0.0,0.69, 0.0 }
#define RLVColor_Purple4_Alpha1 ImVec4{ 0.37,0.0,0.69, 0.2 }
#define RLVColor_Purple4_Alpha2 ImVec4{ 0.37,0.0,0.69, 0.4 }
#define RLVColor_Purple4_Alpha3 ImVec4{ 0.37,0.0,0.69, 0.6 }
#define RLVColor_Purple4_Alpha4 ImVec4{ 0.37,0.0,0.69, 0.8 }
#define RLVColor_Purple4_Alpha5 ImVec4{ 0.37,0.0,0.69, 1.0 }

#define RLVColor_BlueViolet_Alpha0 ImVec4{ 0.37,0.0,1.0, 0.0 }
#define RLVColor_BlueViolet_Alpha1 ImVec4{ 0.37,0.0,1.0, 0.2 }
#define RLVColor_BlueViolet_Alpha2 ImVec4{ 0.37,0.0,1.0, 0.4 }
#define RLVColor_BlueViolet_Alpha3 ImVec4{ 0.37,0.0,1.0, 0.6 }
#define RLVColor_BlueViolet_Alpha4 ImVec4{ 0.37,0.0,1.0, 0.8 }
#define RLVColor_BlueViolet_Alpha5 ImVec4{ 0.37,0.0,1.0, 1.0 }

#define RLVColor_Grey37_Alpha0 ImVec4{ 0.37,0.37,0.37, 0.0 }
#define RLVColor_Grey37_Alpha1 ImVec4{ 0.37,0.37,0.37, 0.2 }
#define RLVColor_Grey37_Alpha2 ImVec4{ 0.37,0.37,0.37, 0.4 }
#define RLVColor_Grey37_Alpha3 ImVec4{ 0.37,0.37,0.37, 0.6 }
#define RLVColor_Grey37_Alpha4 ImVec4{ 0.37,0.37,0.37, 0.8 }
#define RLVColor_Grey37_Alpha5 ImVec4{ 0.37,0.37,0.37, 1.0 }

#define RLVColor_SlateBlue3_Alpha0 ImVec4{ 0.37,0.37,0.69, 0.0 }
#define RLVColor_SlateBlue3_Alpha1 ImVec4{ 0.37,0.37,0.69, 0.2 }
#define RLVColor_SlateBlue3_Alpha2 ImVec4{ 0.37,0.37,0.69, 0.4 }
#define RLVColor_SlateBlue3_Alpha3 ImVec4{ 0.37,0.37,0.69, 0.6 }
#define RLVColor_SlateBlue3_Alpha4 ImVec4{ 0.37,0.37,0.69, 0.8 }
#define RLVColor_SlateBlue3_Alpha5 ImVec4{ 0.37,0.37,0.69, 1.0 }

#define RLVColor_RoyalBlue1_Alpha0 ImVec4{ 0.37,0.37,1.0, 0.0 }
#define RLVColor_RoyalBlue1_Alpha1 ImVec4{ 0.37,0.37,1.0, 0.2 }
#define RLVColor_RoyalBlue1_Alpha2 ImVec4{ 0.37,0.37,1.0, 0.4 }
#define RLVColor_RoyalBlue1_Alpha3 ImVec4{ 0.37,0.37,1.0, 0.6 }
#define RLVColor_RoyalBlue1_Alpha4 ImVec4{ 0.37,0.37,1.0, 0.8 }
#define RLVColor_RoyalBlue1_Alpha5 ImVec4{ 0.37,0.37,1.0, 1.0 }

#define RLVColor_DarkSeaGreen4_Alpha0 ImVec4{ 0.37,0.53,0.37, 0.0 }
#define RLVColor_DarkSeaGreen4_Alpha1 ImVec4{ 0.37,0.53,0.37, 0.2 }
#define RLVColor_DarkSeaGreen4_Alpha2 ImVec4{ 0.37,0.53,0.37, 0.4 }
#define RLVColor_DarkSeaGreen4_Alpha3 ImVec4{ 0.37,0.53,0.37, 0.6 }
#define RLVColor_DarkSeaGreen4_Alpha4 ImVec4{ 0.37,0.53,0.37, 0.8 }
#define RLVColor_DarkSeaGreen4_Alpha5 ImVec4{ 0.37,0.53,0.37, 1.0 }

#define RLVColor_SteelBlue_Alpha0 ImVec4{ 0.37,0.53,0.69, 0.0 }
#define RLVColor_SteelBlue_Alpha1 ImVec4{ 0.37,0.53,0.69, 0.2 }
#define RLVColor_SteelBlue_Alpha2 ImVec4{ 0.37,0.53,0.69, 0.4 }
#define RLVColor_SteelBlue_Alpha3 ImVec4{ 0.37,0.53,0.69, 0.6 }
#define RLVColor_SteelBlue_Alpha4 ImVec4{ 0.37,0.53,0.69, 0.8 }
#define RLVColor_SteelBlue_Alpha5 ImVec4{ 0.37,0.53,0.69, 1.0 }

#define RLVColor_CornflowerBlue_Alpha0 ImVec4{ 0.37,0.53,1.0, 0.0 }
#define RLVColor_CornflowerBlue_Alpha1 ImVec4{ 0.37,0.53,1.0, 0.2 }
#define RLVColor_CornflowerBlue_Alpha2 ImVec4{ 0.37,0.53,1.0, 0.4 }
#define RLVColor_CornflowerBlue_Alpha3 ImVec4{ 0.37,0.53,1.0, 0.6 }
#define RLVColor_CornflowerBlue_Alpha4 ImVec4{ 0.37,0.53,1.0, 0.8 }
#define RLVColor_CornflowerBlue_Alpha5 ImVec4{ 0.37,0.53,1.0, 1.0 }

#define RLVColor_CadetBlue_Alpha0 ImVec4{ 0.37,0.69,0.69, 0.0 }
#define RLVColor_CadetBlue_Alpha1 ImVec4{ 0.37,0.69,0.69, 0.2 }
#define RLVColor_CadetBlue_Alpha2 ImVec4{ 0.37,0.69,0.69, 0.4 }
#define RLVColor_CadetBlue_Alpha3 ImVec4{ 0.37,0.69,0.69, 0.6 }
#define RLVColor_CadetBlue_Alpha4 ImVec4{ 0.37,0.69,0.69, 0.8 }
#define RLVColor_CadetBlue_Alpha5 ImVec4{ 0.37,0.69,0.69, 1.0 }

#define RLVColor_SteelBlue1_Alpha0 ImVec4{ 0.37,0.69,1.0, 0.0 }
#define RLVColor_SteelBlue1_Alpha1 ImVec4{ 0.37,0.69,1.0, 0.2 }
#define RLVColor_SteelBlue1_Alpha2 ImVec4{ 0.37,0.69,1.0, 0.4 }
#define RLVColor_SteelBlue1_Alpha3 ImVec4{ 0.37,0.69,1.0, 0.6 }
#define RLVColor_SteelBlue1_Alpha4 ImVec4{ 0.37,0.69,1.0, 0.8 }
#define RLVColor_SteelBlue1_Alpha5 ImVec4{ 0.37,0.69,1.0, 1.0 }

#define RLVColor_PaleGreen3_Alpha0 ImVec4{ 0.37,0.84,0.37, 0.0 }
#define RLVColor_PaleGreen3_Alpha1 ImVec4{ 0.37,0.84,0.37, 0.2 }
#define RLVColor_PaleGreen3_Alpha2 ImVec4{ 0.37,0.84,0.37, 0.4 }
#define RLVColor_PaleGreen3_Alpha3 ImVec4{ 0.37,0.84,0.37, 0.6 }
#define RLVColor_PaleGreen3_Alpha4 ImVec4{ 0.37,0.84,0.37, 0.8 }
#define RLVColor_PaleGreen3_Alpha5 ImVec4{ 0.37,0.84,0.37, 1.0 }

#define RLVColor_Aquamarine3_Alpha0 ImVec4{ 0.37,0.84,0.69, 0.0 }
#define RLVColor_Aquamarine3_Alpha1 ImVec4{ 0.37,0.84,0.69, 0.2 }
#define RLVColor_Aquamarine3_Alpha2 ImVec4{ 0.37,0.84,0.69, 0.4 }
#define RLVColor_Aquamarine3_Alpha3 ImVec4{ 0.37,0.84,0.69, 0.6 }
#define RLVColor_Aquamarine3_Alpha4 ImVec4{ 0.37,0.84,0.69, 0.8 }
#define RLVColor_Aquamarine3_Alpha5 ImVec4{ 0.37,0.84,0.69, 1.0 }

#define RLVColor_SeaGreen2_Alpha0 ImVec4{ 0.37,1.0,0.37, 0.0 }
#define RLVColor_SeaGreen2_Alpha1 ImVec4{ 0.37,1.0,0.37, 0.2 }
#define RLVColor_SeaGreen2_Alpha2 ImVec4{ 0.37,1.0,0.37, 0.4 }
#define RLVColor_SeaGreen2_Alpha3 ImVec4{ 0.37,1.0,0.37, 0.6 }
#define RLVColor_SeaGreen2_Alpha4 ImVec4{ 0.37,1.0,0.37, 0.8 }
#define RLVColor_SeaGreen2_Alpha5 ImVec4{ 0.37,1.0,0.37, 1.0 }

#define RLVColor_SeaGreen1_Alpha0 ImVec4{ 0.37,1.0,0.69, 0.0 }
#define RLVColor_SeaGreen1_Alpha1 ImVec4{ 0.37,1.0,0.69, 0.2 }
#define RLVColor_SeaGreen1_Alpha2 ImVec4{ 0.37,1.0,0.69, 0.4 }
#define RLVColor_SeaGreen1_Alpha3 ImVec4{ 0.37,1.0,0.69, 0.6 }
#define RLVColor_SeaGreen1_Alpha4 ImVec4{ 0.37,1.0,0.69, 0.8 }
#define RLVColor_SeaGreen1_Alpha5 ImVec4{ 0.37,1.0,0.69, 1.0 }

#define RLVColor_DarkSlateGray2_Alpha0 ImVec4{ 0.37,1.0,1.0, 0.0 }
#define RLVColor_DarkSlateGray2_Alpha1 ImVec4{ 0.37,1.0,1.0, 0.2 }
#define RLVColor_DarkSlateGray2_Alpha2 ImVec4{ 0.37,1.0,1.0, 0.4 }
#define RLVColor_DarkSlateGray2_Alpha3 ImVec4{ 0.37,1.0,1.0, 0.6 }
#define RLVColor_DarkSlateGray2_Alpha4 ImVec4{ 0.37,1.0,1.0, 0.8 }
#define RLVColor_DarkSlateGray2_Alpha5 ImVec4{ 0.37,1.0,1.0, 1.0 }

#define RLVColor_DarkMagenta_Alpha0 ImVec4{ 0.53,0.0,0.69, 0.0 }
#define RLVColor_DarkMagenta_Alpha1 ImVec4{ 0.53,0.0,0.69, 0.2 }
#define RLVColor_DarkMagenta_Alpha2 ImVec4{ 0.53,0.0,0.69, 0.4 }
#define RLVColor_DarkMagenta_Alpha3 ImVec4{ 0.53,0.0,0.69, 0.6 }
#define RLVColor_DarkMagenta_Alpha4 ImVec4{ 0.53,0.0,0.69, 0.8 }
#define RLVColor_DarkMagenta_Alpha5 ImVec4{ 0.53,0.0,0.69, 1.0 }

#define RLVColor_Purple_Alpha0 ImVec4{ 0.53,0.0,1.0, 0.0 }
#define RLVColor_Purple_Alpha1 ImVec4{ 0.53,0.0,1.0, 0.2 }
#define RLVColor_Purple_Alpha2 ImVec4{ 0.53,0.0,1.0, 0.4 }
#define RLVColor_Purple_Alpha3 ImVec4{ 0.53,0.0,1.0, 0.6 }
#define RLVColor_Purple_Alpha4 ImVec4{ 0.53,0.0,1.0, 0.8 }
#define RLVColor_Purple_Alpha5 ImVec4{ 0.53,0.0,1.0, 1.0 }

#define RLVColor_LightPink4_Alpha0 ImVec4{ 0.53,0.37,0.37, 0.0 }
#define RLVColor_LightPink4_Alpha1 ImVec4{ 0.53,0.37,0.37, 0.2 }
#define RLVColor_LightPink4_Alpha2 ImVec4{ 0.53,0.37,0.37, 0.4 }
#define RLVColor_LightPink4_Alpha3 ImVec4{ 0.53,0.37,0.37, 0.6 }
#define RLVColor_LightPink4_Alpha4 ImVec4{ 0.53,0.37,0.37, 0.8 }
#define RLVColor_LightPink4_Alpha5 ImVec4{ 0.53,0.37,0.37, 1.0 }

#define RLVColor_MediumPurple3_Alpha0 ImVec4{ 0.53,0.37,0.69, 0.0 }
#define RLVColor_MediumPurple3_Alpha1 ImVec4{ 0.53,0.37,0.69, 0.2 }
#define RLVColor_MediumPurple3_Alpha2 ImVec4{ 0.53,0.37,0.69, 0.4 }
#define RLVColor_MediumPurple3_Alpha3 ImVec4{ 0.53,0.37,0.69, 0.6 }
#define RLVColor_MediumPurple3_Alpha4 ImVec4{ 0.53,0.37,0.69, 0.8 }
#define RLVColor_MediumPurple3_Alpha5 ImVec4{ 0.53,0.37,0.69, 1.0 }

#define RLVColor_SlateBlue1_Alpha0 ImVec4{ 0.53,0.37,1.0, 0.0 }
#define RLVColor_SlateBlue1_Alpha1 ImVec4{ 0.53,0.37,1.0, 0.2 }
#define RLVColor_SlateBlue1_Alpha2 ImVec4{ 0.53,0.37,1.0, 0.4 }
#define RLVColor_SlateBlue1_Alpha3 ImVec4{ 0.53,0.37,1.0, 0.6 }
#define RLVColor_SlateBlue1_Alpha4 ImVec4{ 0.53,0.37,1.0, 0.8 }
#define RLVColor_SlateBlue1_Alpha5 ImVec4{ 0.53,0.37,1.0, 1.0 }

#define RLVColor_Wheat4_Alpha0 ImVec4{ 0.53,0.53,0.37, 0.0 }
#define RLVColor_Wheat4_Alpha1 ImVec4{ 0.53,0.53,0.37, 0.2 }
#define RLVColor_Wheat4_Alpha2 ImVec4{ 0.53,0.53,0.37, 0.4 }
#define RLVColor_Wheat4_Alpha3 ImVec4{ 0.53,0.53,0.37, 0.6 }
#define RLVColor_Wheat4_Alpha4 ImVec4{ 0.53,0.53,0.37, 0.8 }
#define RLVColor_Wheat4_Alpha5 ImVec4{ 0.53,0.53,0.37, 1.0 }

#define RLVColor_LightSlateGrey_Alpha0 ImVec4{ 0.53,0.53,0.69, 0.0 }
#define RLVColor_LightSlateGrey_Alpha1 ImVec4{ 0.53,0.53,0.69, 0.2 }
#define RLVColor_LightSlateGrey_Alpha2 ImVec4{ 0.53,0.53,0.69, 0.4 }
#define RLVColor_LightSlateGrey_Alpha3 ImVec4{ 0.53,0.53,0.69, 0.6 }
#define RLVColor_LightSlateGrey_Alpha4 ImVec4{ 0.53,0.53,0.69, 0.8 }
#define RLVColor_LightSlateGrey_Alpha5 ImVec4{ 0.53,0.53,0.69, 1.0 }

#define RLVColor_LightSlateBlue_Alpha0 ImVec4{ 0.53,0.53,1.0, 0.0 }
#define RLVColor_LightSlateBlue_Alpha1 ImVec4{ 0.53,0.53,1.0, 0.2 }
#define RLVColor_LightSlateBlue_Alpha2 ImVec4{ 0.53,0.53,1.0, 0.4 }
#define RLVColor_LightSlateBlue_Alpha3 ImVec4{ 0.53,0.53,1.0, 0.6 }
#define RLVColor_LightSlateBlue_Alpha4 ImVec4{ 0.53,0.53,1.0, 0.8 }
#define RLVColor_LightSlateBlue_Alpha5 ImVec4{ 0.53,0.53,1.0, 1.0 }

#define RLVColor_DarkOliveGreen3_Alpha0 ImVec4{ 0.53,0.69,0.37, 0.0 }
#define RLVColor_DarkOliveGreen3_Alpha1 ImVec4{ 0.53,0.69,0.37, 0.2 }
#define RLVColor_DarkOliveGreen3_Alpha2 ImVec4{ 0.53,0.69,0.37, 0.4 }
#define RLVColor_DarkOliveGreen3_Alpha3 ImVec4{ 0.53,0.69,0.37, 0.6 }
#define RLVColor_DarkOliveGreen3_Alpha4 ImVec4{ 0.53,0.69,0.37, 0.8 }
#define RLVColor_DarkOliveGreen3_Alpha5 ImVec4{ 0.53,0.69,0.37, 1.0 }

#define RLVColor_LightSkyBlue3_Alpha0 ImVec4{ 0.53,0.69,0.69, 0.0 }
#define RLVColor_LightSkyBlue3_Alpha1 ImVec4{ 0.53,0.69,0.69, 0.2 }
#define RLVColor_LightSkyBlue3_Alpha2 ImVec4{ 0.53,0.69,0.69, 0.4 }
#define RLVColor_LightSkyBlue3_Alpha3 ImVec4{ 0.53,0.69,0.69, 0.6 }
#define RLVColor_LightSkyBlue3_Alpha4 ImVec4{ 0.53,0.69,0.69, 0.8 }
#define RLVColor_LightSkyBlue3_Alpha5 ImVec4{ 0.53,0.69,0.69, 1.0 }

#define RLVColor_SkyBlue2_Alpha0 ImVec4{ 0.53,0.69,1.0, 0.0 }
#define RLVColor_SkyBlue2_Alpha1 ImVec4{ 0.53,0.69,1.0, 0.2 }
#define RLVColor_SkyBlue2_Alpha2 ImVec4{ 0.53,0.69,1.0, 0.4 }
#define RLVColor_SkyBlue2_Alpha3 ImVec4{ 0.53,0.69,1.0, 0.6 }
#define RLVColor_SkyBlue2_Alpha4 ImVec4{ 0.53,0.69,1.0, 0.8 }
#define RLVColor_SkyBlue2_Alpha5 ImVec4{ 0.53,0.69,1.0, 1.0 }

#define RLVColor_DarkSeaGreen3_Alpha0 ImVec4{ 0.53,0.84,0.69, 0.0 }
#define RLVColor_DarkSeaGreen3_Alpha1 ImVec4{ 0.53,0.84,0.69, 0.2 }
#define RLVColor_DarkSeaGreen3_Alpha2 ImVec4{ 0.53,0.84,0.69, 0.4 }
#define RLVColor_DarkSeaGreen3_Alpha3 ImVec4{ 0.53,0.84,0.69, 0.6 }
#define RLVColor_DarkSeaGreen3_Alpha4 ImVec4{ 0.53,0.84,0.69, 0.8 }
#define RLVColor_DarkSeaGreen3_Alpha5 ImVec4{ 0.53,0.84,0.69, 1.0 }

#define RLVColor_SkyBlue1_Alpha0 ImVec4{ 0.53,0.84,1.0, 0.0 }
#define RLVColor_SkyBlue1_Alpha1 ImVec4{ 0.53,0.84,1.0, 0.2 }
#define RLVColor_SkyBlue1_Alpha2 ImVec4{ 0.53,0.84,1.0, 0.4 }
#define RLVColor_SkyBlue1_Alpha3 ImVec4{ 0.53,0.84,1.0, 0.6 }
#define RLVColor_SkyBlue1_Alpha4 ImVec4{ 0.53,0.84,1.0, 0.8 }
#define RLVColor_SkyBlue1_Alpha5 ImVec4{ 0.53,0.84,1.0, 1.0 }

#define RLVColor_LightGreen_Alpha0 ImVec4{ 0.53,1.0,0.37, 0.0 }
#define RLVColor_LightGreen_Alpha1 ImVec4{ 0.53,1.0,0.37, 0.2 }
#define RLVColor_LightGreen_Alpha2 ImVec4{ 0.53,1.0,0.37, 0.4 }
#define RLVColor_LightGreen_Alpha3 ImVec4{ 0.53,1.0,0.37, 0.6 }
#define RLVColor_LightGreen_Alpha4 ImVec4{ 0.53,1.0,0.37, 0.8 }
#define RLVColor_LightGreen_Alpha5 ImVec4{ 0.53,1.0,0.37, 1.0 }

#define RLVColor_PaleGreen1_Alpha0 ImVec4{ 0.53,1.0,0.69, 0.0 }
#define RLVColor_PaleGreen1_Alpha1 ImVec4{ 0.53,1.0,0.69, 0.2 }
#define RLVColor_PaleGreen1_Alpha2 ImVec4{ 0.53,1.0,0.69, 0.4 }
#define RLVColor_PaleGreen1_Alpha3 ImVec4{ 0.53,1.0,0.69, 0.6 }
#define RLVColor_PaleGreen1_Alpha4 ImVec4{ 0.53,1.0,0.69, 0.8 }
#define RLVColor_PaleGreen1_Alpha5 ImVec4{ 0.53,1.0,0.69, 1.0 }

#define RLVColor_DarkSlateGray1_Alpha0 ImVec4{ 0.53,1.0,1.0, 0.0 }
#define RLVColor_DarkSlateGray1_Alpha1 ImVec4{ 0.53,1.0,1.0, 0.2 }
#define RLVColor_DarkSlateGray1_Alpha2 ImVec4{ 0.53,1.0,1.0, 0.4 }
#define RLVColor_DarkSlateGray1_Alpha3 ImVec4{ 0.53,1.0,1.0, 0.6 }
#define RLVColor_DarkSlateGray1_Alpha4 ImVec4{ 0.53,1.0,1.0, 0.8 }
#define RLVColor_DarkSlateGray1_Alpha5 ImVec4{ 0.53,1.0,1.0, 1.0 }

#define RLVColor_Magenta3_Alpha0 ImVec4{ 0.69,0.0,0.69, 0.0 }
#define RLVColor_Magenta3_Alpha1 ImVec4{ 0.69,0.0,0.69, 0.2 }
#define RLVColor_Magenta3_Alpha2 ImVec4{ 0.69,0.0,0.69, 0.4 }
#define RLVColor_Magenta3_Alpha3 ImVec4{ 0.69,0.0,0.69, 0.6 }
#define RLVColor_Magenta3_Alpha4 ImVec4{ 0.69,0.0,0.69, 0.8 }
#define RLVColor_Magenta3_Alpha5 ImVec4{ 0.69,0.0,0.69, 1.0 }

#define RLVColor_IndianRed_Alpha0 ImVec4{ 0.69,0.37,0.37, 0.0 }
#define RLVColor_IndianRed_Alpha1 ImVec4{ 0.69,0.37,0.37, 0.2 }
#define RLVColor_IndianRed_Alpha2 ImVec4{ 0.69,0.37,0.37, 0.4 }
#define RLVColor_IndianRed_Alpha3 ImVec4{ 0.69,0.37,0.37, 0.6 }
#define RLVColor_IndianRed_Alpha4 ImVec4{ 0.69,0.37,0.37, 0.8 }
#define RLVColor_IndianRed_Alpha5 ImVec4{ 0.69,0.37,0.37, 1.0 }

#define RLVColor_MediumOrchid3_Alpha0 ImVec4{ 0.69,0.37,0.69, 0.0 }
#define RLVColor_MediumOrchid3_Alpha1 ImVec4{ 0.69,0.37,0.69, 0.2 }
#define RLVColor_MediumOrchid3_Alpha2 ImVec4{ 0.69,0.37,0.69, 0.4 }
#define RLVColor_MediumOrchid3_Alpha3 ImVec4{ 0.69,0.37,0.69, 0.6 }
#define RLVColor_MediumOrchid3_Alpha4 ImVec4{ 0.69,0.37,0.69, 0.8 }
#define RLVColor_MediumOrchid3_Alpha5 ImVec4{ 0.69,0.37,0.69, 1.0 }

#define RLVColor_MediumPurple2_Alpha0 ImVec4{ 0.69,0.37,1.0, 0.0 }
#define RLVColor_MediumPurple2_Alpha1 ImVec4{ 0.69,0.37,1.0, 0.2 }
#define RLVColor_MediumPurple2_Alpha2 ImVec4{ 0.69,0.37,1.0, 0.4 }
#define RLVColor_MediumPurple2_Alpha3 ImVec4{ 0.69,0.37,1.0, 0.6 }
#define RLVColor_MediumPurple2_Alpha4 ImVec4{ 0.69,0.37,1.0, 0.8 }
#define RLVColor_MediumPurple2_Alpha5 ImVec4{ 0.69,0.37,1.0, 1.0 }

#define RLVColor_LightSalmon3_Alpha0 ImVec4{ 0.69,0.53,0.37, 0.0 }
#define RLVColor_LightSalmon3_Alpha1 ImVec4{ 0.69,0.53,0.37, 0.2 }
#define RLVColor_LightSalmon3_Alpha2 ImVec4{ 0.69,0.53,0.37, 0.4 }
#define RLVColor_LightSalmon3_Alpha3 ImVec4{ 0.69,0.53,0.37, 0.6 }
#define RLVColor_LightSalmon3_Alpha4 ImVec4{ 0.69,0.53,0.37, 0.8 }
#define RLVColor_LightSalmon3_Alpha5 ImVec4{ 0.69,0.53,0.37, 1.0 }

#define RLVColor_Grey63_Alpha0 ImVec4{ 0.69,0.53,0.69, 0.0 }
#define RLVColor_Grey63_Alpha1 ImVec4{ 0.69,0.53,0.69, 0.2 }
#define RLVColor_Grey63_Alpha2 ImVec4{ 0.69,0.53,0.69, 0.4 }
#define RLVColor_Grey63_Alpha3 ImVec4{ 0.69,0.53,0.69, 0.6 }
#define RLVColor_Grey63_Alpha4 ImVec4{ 0.69,0.53,0.69, 0.8 }
#define RLVColor_Grey63_Alpha5 ImVec4{ 0.69,0.53,0.69, 1.0 }

#define RLVColor_MediumPurple1_Alpha0 ImVec4{ 0.69,0.53,1.0, 0.0 }
#define RLVColor_MediumPurple1_Alpha1 ImVec4{ 0.69,0.53,1.0, 0.2 }
#define RLVColor_MediumPurple1_Alpha2 ImVec4{ 0.69,0.53,1.0, 0.4 }
#define RLVColor_MediumPurple1_Alpha3 ImVec4{ 0.69,0.53,1.0, 0.6 }
#define RLVColor_MediumPurple1_Alpha4 ImVec4{ 0.69,0.53,1.0, 0.8 }
#define RLVColor_MediumPurple1_Alpha5 ImVec4{ 0.69,0.53,1.0, 1.0 }

#define RLVColor_DarkKhaki_Alpha0 ImVec4{ 0.69,0.69,0.37, 0.0 }
#define RLVColor_DarkKhaki_Alpha1 ImVec4{ 0.69,0.69,0.37, 0.2 }
#define RLVColor_DarkKhaki_Alpha2 ImVec4{ 0.69,0.69,0.37, 0.4 }
#define RLVColor_DarkKhaki_Alpha3 ImVec4{ 0.69,0.69,0.37, 0.6 }
#define RLVColor_DarkKhaki_Alpha4 ImVec4{ 0.69,0.69,0.37, 0.8 }
#define RLVColor_DarkKhaki_Alpha5 ImVec4{ 0.69,0.69,0.37, 1.0 }

#define RLVColor_Grey69_Alpha0 ImVec4{ 0.69,0.69,0.69, 0.0 }
#define RLVColor_Grey69_Alpha1 ImVec4{ 0.69,0.69,0.69, 0.2 }
#define RLVColor_Grey69_Alpha2 ImVec4{ 0.69,0.69,0.69, 0.4 }
#define RLVColor_Grey69_Alpha3 ImVec4{ 0.69,0.69,0.69, 0.6 }
#define RLVColor_Grey69_Alpha4 ImVec4{ 0.69,0.69,0.69, 0.8 }
#define RLVColor_Grey69_Alpha5 ImVec4{ 0.69,0.69,0.69, 1.0 }

#define RLVColor_LightSteelBlue_Alpha0 ImVec4{ 0.69,0.69,1.0, 0.0 }
#define RLVColor_LightSteelBlue_Alpha1 ImVec4{ 0.69,0.69,1.0, 0.2 }
#define RLVColor_LightSteelBlue_Alpha2 ImVec4{ 0.69,0.69,1.0, 0.4 }
#define RLVColor_LightSteelBlue_Alpha3 ImVec4{ 0.69,0.69,1.0, 0.6 }
#define RLVColor_LightSteelBlue_Alpha4 ImVec4{ 0.69,0.69,1.0, 0.8 }
#define RLVColor_LightSteelBlue_Alpha5 ImVec4{ 0.69,0.69,1.0, 1.0 }

#define RLVColor_DarkSeaGreen2_Alpha0 ImVec4{ 0.69,0.84,0.69, 0.0 }
#define RLVColor_DarkSeaGreen2_Alpha1 ImVec4{ 0.69,0.84,0.69, 0.2 }
#define RLVColor_DarkSeaGreen2_Alpha2 ImVec4{ 0.69,0.84,0.69, 0.4 }
#define RLVColor_DarkSeaGreen2_Alpha3 ImVec4{ 0.69,0.84,0.69, 0.6 }
#define RLVColor_DarkSeaGreen2_Alpha4 ImVec4{ 0.69,0.84,0.69, 0.8 }
#define RLVColor_DarkSeaGreen2_Alpha5 ImVec4{ 0.69,0.84,0.69, 1.0 }

#define RLVColor_LightSkyBlue1_Alpha0 ImVec4{ 0.69,0.84,1.0, 0.0 }
#define RLVColor_LightSkyBlue1_Alpha1 ImVec4{ 0.69,0.84,1.0, 0.2 }
#define RLVColor_LightSkyBlue1_Alpha2 ImVec4{ 0.69,0.84,1.0, 0.4 }
#define RLVColor_LightSkyBlue1_Alpha3 ImVec4{ 0.69,0.84,1.0, 0.6 }
#define RLVColor_LightSkyBlue1_Alpha4 ImVec4{ 0.69,0.84,1.0, 0.8 }
#define RLVColor_LightSkyBlue1_Alpha5 ImVec4{ 0.69,0.84,1.0, 1.0 }

#define RLVColor_DarkOliveGreen2_Alpha0 ImVec4{ 0.69,1.0,0.37, 0.0 }
#define RLVColor_DarkOliveGreen2_Alpha1 ImVec4{ 0.69,1.0,0.37, 0.2 }
#define RLVColor_DarkOliveGreen2_Alpha2 ImVec4{ 0.69,1.0,0.37, 0.4 }
#define RLVColor_DarkOliveGreen2_Alpha3 ImVec4{ 0.69,1.0,0.37, 0.6 }
#define RLVColor_DarkOliveGreen2_Alpha4 ImVec4{ 0.69,1.0,0.37, 0.8 }
#define RLVColor_DarkOliveGreen2_Alpha5 ImVec4{ 0.69,1.0,0.37, 1.0 }

#define RLVColor_PaleTurquoise1_Alpha0 ImVec4{ 0.69,1.0,1.0, 0.0 }
#define RLVColor_PaleTurquoise1_Alpha1 ImVec4{ 0.69,1.0,1.0, 0.2 }
#define RLVColor_PaleTurquoise1_Alpha2 ImVec4{ 0.69,1.0,1.0, 0.4 }
#define RLVColor_PaleTurquoise1_Alpha3 ImVec4{ 0.69,1.0,1.0, 0.6 }
#define RLVColor_PaleTurquoise1_Alpha4 ImVec4{ 0.69,1.0,1.0, 0.8 }
#define RLVColor_PaleTurquoise1_Alpha5 ImVec4{ 0.69,1.0,1.0, 1.0 }

#define RLVColor_DeepPink3_Alpha0 ImVec4{ 0.84,0.0,0.37, 0.0 }
#define RLVColor_DeepPink3_Alpha1 ImVec4{ 0.84,0.0,0.37, 0.2 }
#define RLVColor_DeepPink3_Alpha2 ImVec4{ 0.84,0.0,0.37, 0.4 }
#define RLVColor_DeepPink3_Alpha3 ImVec4{ 0.84,0.0,0.37, 0.6 }
#define RLVColor_DeepPink3_Alpha4 ImVec4{ 0.84,0.0,0.37, 0.8 }
#define RLVColor_DeepPink3_Alpha5 ImVec4{ 0.84,0.0,0.37, 1.0 }

#define RLVColor_Magenta2_Alpha0 ImVec4{ 0.84,0.0,1.0, 0.0 }
#define RLVColor_Magenta2_Alpha1 ImVec4{ 0.84,0.0,1.0, 0.2 }
#define RLVColor_Magenta2_Alpha2 ImVec4{ 0.84,0.0,1.0, 0.4 }
#define RLVColor_Magenta2_Alpha3 ImVec4{ 0.84,0.0,1.0, 0.6 }
#define RLVColor_Magenta2_Alpha4 ImVec4{ 0.84,0.0,1.0, 0.8 }
#define RLVColor_Magenta2_Alpha5 ImVec4{ 0.84,0.0,1.0, 1.0 }

#define RLVColor_HotPink2_Alpha0 ImVec4{ 0.84,0.37,0.69, 0.0 }
#define RLVColor_HotPink2_Alpha1 ImVec4{ 0.84,0.37,0.69, 0.2 }
#define RLVColor_HotPink2_Alpha2 ImVec4{ 0.84,0.37,0.69, 0.4 }
#define RLVColor_HotPink2_Alpha3 ImVec4{ 0.84,0.37,0.69, 0.6 }
#define RLVColor_HotPink2_Alpha4 ImVec4{ 0.84,0.37,0.69, 0.8 }
#define RLVColor_HotPink2_Alpha5 ImVec4{ 0.84,0.37,0.69, 1.0 }

#define RLVColor_MediumOrchid1_Alpha0 ImVec4{ 0.84,0.37,1.0, 0.0 }
#define RLVColor_MediumOrchid1_Alpha1 ImVec4{ 0.84,0.37,1.0, 0.2 }
#define RLVColor_MediumOrchid1_Alpha2 ImVec4{ 0.84,0.37,1.0, 0.4 }
#define RLVColor_MediumOrchid1_Alpha3 ImVec4{ 0.84,0.37,1.0, 0.6 }
#define RLVColor_MediumOrchid1_Alpha4 ImVec4{ 0.84,0.37,1.0, 0.8 }
#define RLVColor_MediumOrchid1_Alpha5 ImVec4{ 0.84,0.37,1.0, 1.0 }

#define RLVColor_Pink3_Alpha0 ImVec4{ 0.84,0.53,0.69, 0.0 }
#define RLVColor_Pink3_Alpha1 ImVec4{ 0.84,0.53,0.69, 0.2 }
#define RLVColor_Pink3_Alpha2 ImVec4{ 0.84,0.53,0.69, 0.4 }
#define RLVColor_Pink3_Alpha3 ImVec4{ 0.84,0.53,0.69, 0.6 }
#define RLVColor_Pink3_Alpha4 ImVec4{ 0.84,0.53,0.69, 0.8 }
#define RLVColor_Pink3_Alpha5 ImVec4{ 0.84,0.53,0.69, 1.0 }

#define RLVColor_Violet_Alpha0 ImVec4{ 0.84,0.53,1.0, 0.0 }
#define RLVColor_Violet_Alpha1 ImVec4{ 0.84,0.53,1.0, 0.2 }
#define RLVColor_Violet_Alpha2 ImVec4{ 0.84,0.53,1.0, 0.4 }
#define RLVColor_Violet_Alpha3 ImVec4{ 0.84,0.53,1.0, 0.6 }
#define RLVColor_Violet_Alpha4 ImVec4{ 0.84,0.53,1.0, 0.8 }
#define RLVColor_Violet_Alpha5 ImVec4{ 0.84,0.53,1.0, 1.0 }

#define RLVColor_LightGoldenrod3_Alpha0 ImVec4{ 0.84,0.69,0.37, 0.0 }
#define RLVColor_LightGoldenrod3_Alpha1 ImVec4{ 0.84,0.69,0.37, 0.2 }
#define RLVColor_LightGoldenrod3_Alpha2 ImVec4{ 0.84,0.69,0.37, 0.4 }
#define RLVColor_LightGoldenrod3_Alpha3 ImVec4{ 0.84,0.69,0.37, 0.6 }
#define RLVColor_LightGoldenrod3_Alpha4 ImVec4{ 0.84,0.69,0.37, 0.8 }
#define RLVColor_LightGoldenrod3_Alpha5 ImVec4{ 0.84,0.69,0.37, 1.0 }

#define RLVColor_MistyRose3_Alpha0 ImVec4{ 0.84,0.69,0.69, 0.0 }
#define RLVColor_MistyRose3_Alpha1 ImVec4{ 0.84,0.69,0.69, 0.2 }
#define RLVColor_MistyRose3_Alpha2 ImVec4{ 0.84,0.69,0.69, 0.4 }
#define RLVColor_MistyRose3_Alpha3 ImVec4{ 0.84,0.69,0.69, 0.6 }
#define RLVColor_MistyRose3_Alpha4 ImVec4{ 0.84,0.69,0.69, 0.8 }
#define RLVColor_MistyRose3_Alpha5 ImVec4{ 0.84,0.69,0.69, 1.0 }

#define RLVColor_Plum2_Alpha0 ImVec4{ 0.84,0.69,1.0, 0.0 }
#define RLVColor_Plum2_Alpha1 ImVec4{ 0.84,0.69,1.0, 0.2 }
#define RLVColor_Plum2_Alpha2 ImVec4{ 0.84,0.69,1.0, 0.4 }
#define RLVColor_Plum2_Alpha3 ImVec4{ 0.84,0.69,1.0, 0.6 }
#define RLVColor_Plum2_Alpha4 ImVec4{ 0.84,0.69,1.0, 0.8 }
#define RLVColor_Plum2_Alpha5 ImVec4{ 0.84,0.69,1.0, 1.0 }

#define RLVColor_Khaki3_Alpha0 ImVec4{ 0.84,0.84,0.37, 0.0 }
#define RLVColor_Khaki3_Alpha1 ImVec4{ 0.84,0.84,0.37, 0.2 }
#define RLVColor_Khaki3_Alpha2 ImVec4{ 0.84,0.84,0.37, 0.4 }
#define RLVColor_Khaki3_Alpha3 ImVec4{ 0.84,0.84,0.37, 0.6 }
#define RLVColor_Khaki3_Alpha4 ImVec4{ 0.84,0.84,0.37, 0.8 }
#define RLVColor_Khaki3_Alpha5 ImVec4{ 0.84,0.84,0.37, 1.0 }

#define RLVColor_LightYellow3_Alpha0 ImVec4{ 0.84,0.84,0.69, 0.0 }
#define RLVColor_LightYellow3_Alpha1 ImVec4{ 0.84,0.84,0.69, 0.2 }
#define RLVColor_LightYellow3_Alpha2 ImVec4{ 0.84,0.84,0.69, 0.4 }
#define RLVColor_LightYellow3_Alpha3 ImVec4{ 0.84,0.84,0.69, 0.6 }
#define RLVColor_LightYellow3_Alpha4 ImVec4{ 0.84,0.84,0.69, 0.8 }
#define RLVColor_LightYellow3_Alpha5 ImVec4{ 0.84,0.84,0.69, 1.0 }

#define RLVColor_LightSteelBlue1_Alpha0 ImVec4{ 0.84,0.84,1.0, 0.0 }
#define RLVColor_LightSteelBlue1_Alpha1 ImVec4{ 0.84,0.84,1.0, 0.2 }
#define RLVColor_LightSteelBlue1_Alpha2 ImVec4{ 0.84,0.84,1.0, 0.4 }
#define RLVColor_LightSteelBlue1_Alpha3 ImVec4{ 0.84,0.84,1.0, 0.6 }
#define RLVColor_LightSteelBlue1_Alpha4 ImVec4{ 0.84,0.84,1.0, 0.8 }
#define RLVColor_LightSteelBlue1_Alpha5 ImVec4{ 0.84,0.84,1.0, 1.0 }

#define RLVColor_DarkOliveGreen1_Alpha0 ImVec4{ 0.84,1.0,0.37, 0.0 }
#define RLVColor_DarkOliveGreen1_Alpha1 ImVec4{ 0.84,1.0,0.37, 0.2 }
#define RLVColor_DarkOliveGreen1_Alpha2 ImVec4{ 0.84,1.0,0.37, 0.4 }
#define RLVColor_DarkOliveGreen1_Alpha3 ImVec4{ 0.84,1.0,0.37, 0.6 }
#define RLVColor_DarkOliveGreen1_Alpha4 ImVec4{ 0.84,1.0,0.37, 0.8 }
#define RLVColor_DarkOliveGreen1_Alpha5 ImVec4{ 0.84,1.0,0.37, 1.0 }

#define RLVColor_DarkSeaGreen1_Alpha0 ImVec4{ 0.84,1.0,0.69, 0.0 }
#define RLVColor_DarkSeaGreen1_Alpha1 ImVec4{ 0.84,1.0,0.69, 0.2 }
#define RLVColor_DarkSeaGreen1_Alpha2 ImVec4{ 0.84,1.0,0.69, 0.4 }
#define RLVColor_DarkSeaGreen1_Alpha3 ImVec4{ 0.84,1.0,0.69, 0.6 }
#define RLVColor_DarkSeaGreen1_Alpha4 ImVec4{ 0.84,1.0,0.69, 0.8 }
#define RLVColor_DarkSeaGreen1_Alpha5 ImVec4{ 0.84,1.0,0.69, 1.0 }

#define RLVColor_LightCyan1_Alpha0 ImVec4{ 0.84,1.0,1.0, 0.0 }
#define RLVColor_LightCyan1_Alpha1 ImVec4{ 0.84,1.0,1.0, 0.2 }
#define RLVColor_LightCyan1_Alpha2 ImVec4{ 0.84,1.0,1.0, 0.4 }
#define RLVColor_LightCyan1_Alpha3 ImVec4{ 0.84,1.0,1.0, 0.6 }
#define RLVColor_LightCyan1_Alpha4 ImVec4{ 0.84,1.0,1.0, 0.8 }
#define RLVColor_LightCyan1_Alpha5 ImVec4{ 0.84,1.0,1.0, 1.0 }

#define RLVColor_DeepPink2_Alpha0 ImVec4{ 1.0,0.0,0.37, 0.0 }
#define RLVColor_DeepPink2_Alpha1 ImVec4{ 1.0,0.0,0.37, 0.2 }
#define RLVColor_DeepPink2_Alpha2 ImVec4{ 1.0,0.0,0.37, 0.4 }
#define RLVColor_DeepPink2_Alpha3 ImVec4{ 1.0,0.0,0.37, 0.6 }
#define RLVColor_DeepPink2_Alpha4 ImVec4{ 1.0,0.0,0.37, 0.8 }
#define RLVColor_DeepPink2_Alpha5 ImVec4{ 1.0,0.0,0.37, 1.0 }

#define RLVColor_DeepPink1_Alpha0 ImVec4{ 1.0,0.0,0.69, 0.0 }
#define RLVColor_DeepPink1_Alpha1 ImVec4{ 1.0,0.0,0.69, 0.2 }
#define RLVColor_DeepPink1_Alpha2 ImVec4{ 1.0,0.0,0.69, 0.4 }
#define RLVColor_DeepPink1_Alpha3 ImVec4{ 1.0,0.0,0.69, 0.6 }
#define RLVColor_DeepPink1_Alpha4 ImVec4{ 1.0,0.0,0.69, 0.8 }
#define RLVColor_DeepPink1_Alpha5 ImVec4{ 1.0,0.0,0.69, 1.0 }

#define RLVColor_Magenta1_Alpha0 ImVec4{ 1.0,0.0,1.0, 0.0 }
#define RLVColor_Magenta1_Alpha1 ImVec4{ 1.0,0.0,1.0, 0.2 }
#define RLVColor_Magenta1_Alpha2 ImVec4{ 1.0,0.0,1.0, 0.4 }
#define RLVColor_Magenta1_Alpha3 ImVec4{ 1.0,0.0,1.0, 0.6 }
#define RLVColor_Magenta1_Alpha4 ImVec4{ 1.0,0.0,1.0, 0.8 }
#define RLVColor_Magenta1_Alpha5 ImVec4{ 1.0,0.0,1.0, 1.0 }

#define RLVColor_IndianRed1_Alpha0 ImVec4{ 1.0,0.37,0.37, 0.0 }
#define RLVColor_IndianRed1_Alpha1 ImVec4{ 1.0,0.37,0.37, 0.2 }
#define RLVColor_IndianRed1_Alpha2 ImVec4{ 1.0,0.37,0.37, 0.4 }
#define RLVColor_IndianRed1_Alpha3 ImVec4{ 1.0,0.37,0.37, 0.6 }
#define RLVColor_IndianRed1_Alpha4 ImVec4{ 1.0,0.37,0.37, 0.8 }
#define RLVColor_IndianRed1_Alpha5 ImVec4{ 1.0,0.37,0.37, 1.0 }

#define RLVColor_HotPink_Alpha0 ImVec4{ 1.0,0.37,0.69, 0.0 }
#define RLVColor_HotPink_Alpha1 ImVec4{ 1.0,0.37,0.69, 0.2 }
#define RLVColor_HotPink_Alpha2 ImVec4{ 1.0,0.37,0.69, 0.4 }
#define RLVColor_HotPink_Alpha3 ImVec4{ 1.0,0.37,0.69, 0.6 }
#define RLVColor_HotPink_Alpha4 ImVec4{ 1.0,0.37,0.69, 0.8 }
#define RLVColor_HotPink_Alpha5 ImVec4{ 1.0,0.37,0.69, 1.0 }

#define RLVColor_Salmon1_Alpha0 ImVec4{ 1.0,0.53,0.37, 0.0 }
#define RLVColor_Salmon1_Alpha1 ImVec4{ 1.0,0.53,0.37, 0.2 }
#define RLVColor_Salmon1_Alpha2 ImVec4{ 1.0,0.53,0.37, 0.4 }
#define RLVColor_Salmon1_Alpha3 ImVec4{ 1.0,0.53,0.37, 0.6 }
#define RLVColor_Salmon1_Alpha4 ImVec4{ 1.0,0.53,0.37, 0.8 }
#define RLVColor_Salmon1_Alpha5 ImVec4{ 1.0,0.53,0.37, 1.0 }

#define RLVColor_PaleVioletRed1_Alpha0 ImVec4{ 1.0,0.53,0.69, 0.0 }
#define RLVColor_PaleVioletRed1_Alpha1 ImVec4{ 1.0,0.53,0.69, 0.2 }
#define RLVColor_PaleVioletRed1_Alpha2 ImVec4{ 1.0,0.53,0.69, 0.4 }
#define RLVColor_PaleVioletRed1_Alpha3 ImVec4{ 1.0,0.53,0.69, 0.6 }
#define RLVColor_PaleVioletRed1_Alpha4 ImVec4{ 1.0,0.53,0.69, 0.8 }
#define RLVColor_PaleVioletRed1_Alpha5 ImVec4{ 1.0,0.53,0.69, 1.0 }

#define RLVColor_Orchid1_Alpha0 ImVec4{ 1.0,0.53,1.0, 0.0 }
#define RLVColor_Orchid1_Alpha1 ImVec4{ 1.0,0.53,1.0, 0.2 }
#define RLVColor_Orchid1_Alpha2 ImVec4{ 1.0,0.53,1.0, 0.4 }
#define RLVColor_Orchid1_Alpha3 ImVec4{ 1.0,0.53,1.0, 0.6 }
#define RLVColor_Orchid1_Alpha4 ImVec4{ 1.0,0.53,1.0, 0.8 }
#define RLVColor_Orchid1_Alpha5 ImVec4{ 1.0,0.53,1.0, 1.0 }

#define RLVColor_SandyBrown_Alpha0 ImVec4{ 1.0,0.69,0.37, 0.0 }
#define RLVColor_SandyBrown_Alpha1 ImVec4{ 1.0,0.69,0.37, 0.2 }
#define RLVColor_SandyBrown_Alpha2 ImVec4{ 1.0,0.69,0.37, 0.4 }
#define RLVColor_SandyBrown_Alpha3 ImVec4{ 1.0,0.69,0.37, 0.6 }
#define RLVColor_SandyBrown_Alpha4 ImVec4{ 1.0,0.69,0.37, 0.8 }
#define RLVColor_SandyBrown_Alpha5 ImVec4{ 1.0,0.69,0.37, 1.0 }

#define RLVColor_LightPink1_Alpha0 ImVec4{ 1.0,0.69,0.69, 0.0 }
#define RLVColor_LightPink1_Alpha1 ImVec4{ 1.0,0.69,0.69, 0.2 }
#define RLVColor_LightPink1_Alpha2 ImVec4{ 1.0,0.69,0.69, 0.4 }
#define RLVColor_LightPink1_Alpha3 ImVec4{ 1.0,0.69,0.69, 0.6 }
#define RLVColor_LightPink1_Alpha4 ImVec4{ 1.0,0.69,0.69, 0.8 }
#define RLVColor_LightPink1_Alpha5 ImVec4{ 1.0,0.69,0.69, 1.0 }

#define RLVColor_Plum1_Alpha0 ImVec4{ 1.0,0.69,1.0, 0.0 }
#define RLVColor_Plum1_Alpha1 ImVec4{ 1.0,0.69,1.0, 0.2 }
#define RLVColor_Plum1_Alpha2 ImVec4{ 1.0,0.69,1.0, 0.4 }
#define RLVColor_Plum1_Alpha3 ImVec4{ 1.0,0.69,1.0, 0.6 }
#define RLVColor_Plum1_Alpha4 ImVec4{ 1.0,0.69,1.0, 0.8 }
#define RLVColor_Plum1_Alpha5 ImVec4{ 1.0,0.69,1.0, 1.0 }

#define RLVColor_LightGoldenrod2_Alpha0 ImVec4{ 1.0,0.84,0.37, 0.0 }
#define RLVColor_LightGoldenrod2_Alpha1 ImVec4{ 1.0,0.84,0.37, 0.2 }
#define RLVColor_LightGoldenrod2_Alpha2 ImVec4{ 1.0,0.84,0.37, 0.4 }
#define RLVColor_LightGoldenrod2_Alpha3 ImVec4{ 1.0,0.84,0.37, 0.6 }
#define RLVColor_LightGoldenrod2_Alpha4 ImVec4{ 1.0,0.84,0.37, 0.8 }
#define RLVColor_LightGoldenrod2_Alpha5 ImVec4{ 1.0,0.84,0.37, 1.0 }

#define RLVColor_NavajoWhite1_Alpha0 ImVec4{ 1.0,0.84,0.69, 0.0 }
#define RLVColor_NavajoWhite1_Alpha1 ImVec4{ 1.0,0.84,0.69, 0.2 }
#define RLVColor_NavajoWhite1_Alpha2 ImVec4{ 1.0,0.84,0.69, 0.4 }
#define RLVColor_NavajoWhite1_Alpha3 ImVec4{ 1.0,0.84,0.69, 0.6 }
#define RLVColor_NavajoWhite1_Alpha4 ImVec4{ 1.0,0.84,0.69, 0.8 }
#define RLVColor_NavajoWhite1_Alpha5 ImVec4{ 1.0,0.84,0.69, 1.0 }

#define RLVColor_Thistle1_Alpha0 ImVec4{ 1.0,0.84,1.0, 0.0 }
#define RLVColor_Thistle1_Alpha1 ImVec4{ 1.0,0.84,1.0, 0.2 }
#define RLVColor_Thistle1_Alpha2 ImVec4{ 1.0,0.84,1.0, 0.4 }
#define RLVColor_Thistle1_Alpha3 ImVec4{ 1.0,0.84,1.0, 0.6 }
#define RLVColor_Thistle1_Alpha4 ImVec4{ 1.0,0.84,1.0, 0.8 }
#define RLVColor_Thistle1_Alpha5 ImVec4{ 1.0,0.84,1.0, 1.0 }

#define RLVColor_LightGoldenrod1_Alpha0 ImVec4{ 1.0,1.0,0.37, 0.0 }
#define RLVColor_LightGoldenrod1_Alpha1 ImVec4{ 1.0,1.0,0.37, 0.2 }
#define RLVColor_LightGoldenrod1_Alpha2 ImVec4{ 1.0,1.0,0.37, 0.4 }
#define RLVColor_LightGoldenrod1_Alpha3 ImVec4{ 1.0,1.0,0.37, 0.6 }
#define RLVColor_LightGoldenrod1_Alpha4 ImVec4{ 1.0,1.0,0.37, 0.8 }
#define RLVColor_LightGoldenrod1_Alpha5 ImVec4{ 1.0,1.0,0.37, 1.0 }

#define RLVColor_Wheat1_Alpha0 ImVec4{ 1.0,1.0,0.69, 0.0 }
#define RLVColor_Wheat1_Alpha1 ImVec4{ 1.0,1.0,0.69, 0.2 }
#define RLVColor_Wheat1_Alpha2 ImVec4{ 1.0,1.0,0.69, 0.4 }
#define RLVColor_Wheat1_Alpha3 ImVec4{ 1.0,1.0,0.69, 0.6 }
#define RLVColor_Wheat1_Alpha4 ImVec4{ 1.0,1.0,0.69, 0.8 }
#define RLVColor_Wheat1_Alpha5 ImVec4{ 1.0,1.0,0.69, 1.0 }

#define RLVColor_Grey100_Alpha0 ImVec4{ 1.0,1.0,1.0, 0.0 }
#define RLVColor_Grey100_Alpha1 ImVec4{ 1.0,1.0,1.0, 0.2 }
#define RLVColor_Grey100_Alpha2 ImVec4{ 1.0,1.0,1.0, 0.4 }
#define RLVColor_Grey100_Alpha3 ImVec4{ 1.0,1.0,1.0, 0.6 }
#define RLVColor_Grey100_Alpha4 ImVec4{ 1.0,1.0,1.0, 0.8 }
#define RLVColor_Grey100_Alpha5 ImVec4{ 1.0,1.0,1.0, 1.0 }

#define RLVColor_Grey7_Alpha0 ImVec4{ 0.07,0.07,0.07, 0.0 }
#define RLVColor_Grey7_Alpha1 ImVec4{ 0.07,0.07,0.07, 0.2 }
#define RLVColor_Grey7_Alpha2 ImVec4{ 0.07,0.07,0.07, 0.4 }
#define RLVColor_Grey7_Alpha3 ImVec4{ 0.07,0.07,0.07, 0.6 }
#define RLVColor_Grey7_Alpha4 ImVec4{ 0.07,0.07,0.07, 0.8 }
#define RLVColor_Grey7_Alpha5 ImVec4{ 0.07,0.07,0.07, 1.0 }

#define RLVColor_Grey15_Alpha0 ImVec4{ 0.15,0.15,0.15, 0.0 }
#define RLVColor_Grey15_Alpha1 ImVec4{ 0.15,0.15,0.15, 0.2 }
#define RLVColor_Grey15_Alpha2 ImVec4{ 0.15,0.15,0.15, 0.4 }
#define RLVColor_Grey15_Alpha3 ImVec4{ 0.15,0.15,0.15, 0.6 }
#define RLVColor_Grey15_Alpha4 ImVec4{ 0.15,0.15,0.15, 0.8 }
#define RLVColor_Grey15_Alpha5 ImVec4{ 0.15,0.15,0.15, 1.0 }

#define RLVColor_Grey23_Alpha0 ImVec4{ 0.23,0.23,0.23, 0.0 }
#define RLVColor_Grey23_Alpha1 ImVec4{ 0.23,0.23,0.23, 0.2 }
#define RLVColor_Grey23_Alpha2 ImVec4{ 0.23,0.23,0.23, 0.4 }
#define RLVColor_Grey23_Alpha3 ImVec4{ 0.23,0.23,0.23, 0.6 }
#define RLVColor_Grey23_Alpha4 ImVec4{ 0.23,0.23,0.23, 0.8 }
#define RLVColor_Grey23_Alpha5 ImVec4{ 0.23,0.23,0.23, 1.0 }

#define RLVColor_Grey30_Alpha0 ImVec4{ 0.31,0.31,0.31, 0.0 }
#define RLVColor_Grey30_Alpha1 ImVec4{ 0.31,0.31,0.31, 0.2 }
#define RLVColor_Grey30_Alpha2 ImVec4{ 0.31,0.31,0.31, 0.4 }
#define RLVColor_Grey30_Alpha3 ImVec4{ 0.31,0.31,0.31, 0.6 }
#define RLVColor_Grey30_Alpha4 ImVec4{ 0.31,0.31,0.31, 0.8 }
#define RLVColor_Grey30_Alpha5 ImVec4{ 0.31,0.31,0.31, 1.0 }

#define RLVColor_Grey39_Alpha0 ImVec4{ 0.38,0.38,0.38, 0.0 }
#define RLVColor_Grey39_Alpha1 ImVec4{ 0.38,0.38,0.38, 0.2 }
#define RLVColor_Grey39_Alpha2 ImVec4{ 0.38,0.38,0.38, 0.4 }
#define RLVColor_Grey39_Alpha3 ImVec4{ 0.38,0.38,0.38, 0.6 }
#define RLVColor_Grey39_Alpha4 ImVec4{ 0.38,0.38,0.38, 0.8 }
#define RLVColor_Grey39_Alpha5 ImVec4{ 0.38,0.38,0.38, 1.0 }

#define RLVColor_Grey46_Alpha0 ImVec4{ 0.46,0.46,0.46, 0.0 }
#define RLVColor_Grey46_Alpha1 ImVec4{ 0.46,0.46,0.46, 0.2 }
#define RLVColor_Grey46_Alpha2 ImVec4{ 0.46,0.46,0.46, 0.4 }
#define RLVColor_Grey46_Alpha3 ImVec4{ 0.46,0.46,0.46, 0.6 }
#define RLVColor_Grey46_Alpha4 ImVec4{ 0.46,0.46,0.46, 0.8 }
#define RLVColor_Grey46_Alpha5 ImVec4{ 0.46,0.46,0.46, 1.0 }

#define RLVColor_Grey54_Alpha0 ImVec4{ 0.54,0.54,0.54, 0.0 }
#define RLVColor_Grey54_Alpha1 ImVec4{ 0.54,0.54,0.54, 0.2 }
#define RLVColor_Grey54_Alpha2 ImVec4{ 0.54,0.54,0.54, 0.4 }
#define RLVColor_Grey54_Alpha3 ImVec4{ 0.54,0.54,0.54, 0.6 }
#define RLVColor_Grey54_Alpha4 ImVec4{ 0.54,0.54,0.54, 0.8 }
#define RLVColor_Grey54_Alpha5 ImVec4{ 0.54,0.54,0.54, 1.0 }

#define RLVColor_Grey62_Alpha0 ImVec4{ 0.62,0.62,0.62, 0.0 }
#define RLVColor_Grey62_Alpha1 ImVec4{ 0.62,0.62,0.62, 0.2 }
#define RLVColor_Grey62_Alpha2 ImVec4{ 0.62,0.62,0.62, 0.4 }
#define RLVColor_Grey62_Alpha3 ImVec4{ 0.62,0.62,0.62, 0.6 }
#define RLVColor_Grey62_Alpha4 ImVec4{ 0.62,0.62,0.62, 0.8 }
#define RLVColor_Grey62_Alpha5 ImVec4{ 0.62,0.62,0.62, 1.0 }

#define RLVColor_Grey70_Alpha0 ImVec4{ 0.7,0.7,0.7, 0.0 }
#define RLVColor_Grey70_Alpha1 ImVec4{ 0.7,0.7,0.7, 0.2 }
#define RLVColor_Grey70_Alpha2 ImVec4{ 0.7,0.7,0.7, 0.4 }
#define RLVColor_Grey70_Alpha3 ImVec4{ 0.7,0.7,0.7, 0.6 }
#define RLVColor_Grey70_Alpha4 ImVec4{ 0.7,0.7,0.7, 0.8 }
#define RLVColor_Grey70_Alpha5 ImVec4{ 0.7,0.7,0.7, 1.0 }

#define RLVColor_Grey78_Alpha0 ImVec4{ 0.78,0.78,0.78, 0.0 }
#define RLVColor_Grey78_Alpha1 ImVec4{ 0.78,0.78,0.78, 0.2 }
#define RLVColor_Grey78_Alpha2 ImVec4{ 0.78,0.78,0.78, 0.4 }
#define RLVColor_Grey78_Alpha3 ImVec4{ 0.78,0.78,0.78, 0.6 }
#define RLVColor_Grey78_Alpha4 ImVec4{ 0.78,0.78,0.78, 0.8 }
#define RLVColor_Grey78_Alpha5 ImVec4{ 0.78,0.78,0.78, 1.0 }

#define RLVColor_Grey85_Alpha0 ImVec4{ 0.85,0.85,0.85, 0.0 }
#define RLVColor_Grey85_Alpha1 ImVec4{ 0.85,0.85,0.85, 0.2 }
#define RLVColor_Grey85_Alpha2 ImVec4{ 0.85,0.85,0.85, 0.4 }
#define RLVColor_Grey85_Alpha3 ImVec4{ 0.85,0.85,0.85, 0.6 }
#define RLVColor_Grey85_Alpha4 ImVec4{ 0.85,0.85,0.85, 0.8 }
#define RLVColor_Grey85_Alpha5 ImVec4{ 0.85,0.85,0.85, 1.0 }

#define RLVColor_Grey93_Alpha0 ImVec4{ 0.93,0.93,0.93, 0.0 }
#define RLVColor_Grey93_Alpha1 ImVec4{ 0.93,0.93,0.93, 0.2 }
#define RLVColor_Grey93_Alpha2 ImVec4{ 0.93,0.93,0.93, 0.4 }
#define RLVColor_Grey93_Alpha3 ImVec4{ 0.93,0.93,0.93, 0.6 }
#define RLVColor_Grey93_Alpha4 ImVec4{ 0.93,0.93,0.93, 0.8 }
#define RLVColor_Grey93_Alpha5 ImVec4{ 0.93,0.93,0.93, 1.0 }
```

