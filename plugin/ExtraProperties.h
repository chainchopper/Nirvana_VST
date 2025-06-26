// Copyright 2022-2024 Filipe Coelho <falktx@falktx.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#define DISTRHO_PLUGIN_WANT_PROGRAMS   1
#define DISTRHO_PLUGIN_WANT_STATE      1
#define DISTRHO_PLUGIN_WANT_FULL_STATE 1
#define DISTRHO_PLUGIN_HAS_UI          1
#define DISTRHO_UI_FILE_BROWSER        1
#define DISTRHO_UI_USE_NANOVG          1
#define DISTRHO_UI_USER_RESIZABLE      0

// we know what we are doing
#define DISTRHO_NO_WARNINGS
#define DISTRHO_PLUGIN_WANT_FULL_STATE_WITH_LADSPA

#define DISTRHO_UI_DEFAULT_WIDTH 1030
#define DISTRHO_UI_DEFAULT_HEIGHT 597

#define DISTRHO_PLUGIN_CLAP_ID "trummerschlunk.master_me"
#define DISTRHO_PLUGIN_BRAND_ID KlSc
#define DISTRHO_PLUGIN_UNIQUE_ID SndG

#define DPF_VST3_DONT_USE_BRAND_ID

#ifdef __MOD_DEVICES__
#define DISTRHO_PLUGIN_USES_MODGUI 1
#define DISTRHO_PLUGIN_USES_CUSTOM_MODGUI 0
#define MASTER_ME_SHARED_MEMORY 0
#else
#define MASTER_ME_SHARED_MEMORY 1
#endif

static constexpr const struct EasyPreset {
    const char* const name;
    float values[61];
} kEasyPresets[] = {
    {
        "YOUTUBE -14 LUFS",
        {0,-14,0,0,0,0,1,0,1,-90,1,50,500,0,20,0,0,600,1,0,50,-20,30,30,1,15,-6,5,50,9,60,50,0,50,0,20,-6,10,80,12,70,60,40,-8,0,50,12,30,8000,1,0,80,3,1,40,3,50,0,0,-1,75},
    },
    {
        "APPLE PODCASTS -16 LUFS",
        {0,-16,0,0,0,0,1,0,1,-90,1,50,500,0,20,0,0,600,1,0,50,-20,30,30,1,15,-6,5,50,9,60,50,0,50,0,20,-6,10,80,12,70,60,40,-8,0,50,12,30,8000,1,0,80,3,1,40,3,50,0,0,-1,75},
    },
    {
        "EBU R128 -23 LUFS",
        {0,-23,0,0,0,0,1,0,1,-90,1,50,500,0,20,0,0,600,1,0,40,-20,30,30,1,15,-6,5,50,9,60,50,0,50,0,20,-6,10,80,12,70,60,40,-8,0,50,12,30,8000,1,0,80,3,1,40,3,50,0,0,-1,75},
    },
    {
        "SPEECH GENERAL -16 LUFS",
        {0,-16,0,0,0,0,1,0,1,-90,1,50,500,0,20,0,0,600,1,0,40,-20,30,30,0,15,-6,5,50,9,60,50,0,50,0,20,-5,10,80,12,70,60,40,-7,0,50,12,30,8000,1,0,80,3,1,40,3,50,0,0,-1,75},
    },
    {
        "MUSIC GENERAL -16 LUFS",
        {0,-16,0,0,0,0,0,0,1,-90,0,50,430.5,0,5,0,1,600,1,0,20,-10,10,10,0,20,-4,20,340,6,60,50,0,50,0,10,-3,15,150,12,70,60,30,-12,8,30,12,30,8000,1,0,80,6,3,40,3,50,0,0,-1,75},
    },
};

enum ExtraParameters {
    kExtraParameterHistogramBufferSize,
#if ! MASTER_ME_SHARED_MEMORY
    kExtraParameterHistogramValueIn,
    kExtraParameterHistogramValueOut,
#endif
    kExtraParameterCount
};

enum ExtraPrograms {
    kExtraProgramCount = sizeof(kEasyPresets)/sizeof(kEasyPresets[0]),
};

enum ExtraStates {
    kExtraStateMode = 0,
    kExtraStateCount
};

static constexpr const uint kMinimumHistogramBufferSize = 4096;

#if MASTER_ME_SHARED_MEMORY
#include "utils/FloatFifo.hpp"

typedef FloatFifo<128> MasterMeFloatFifo;
typedef FloatFifoControl<128> MasterMeFifoControl;

struct MasterMeHistogramFifos {
    MasterMeFloatFifo lufsIn;
    MasterMeFloatFifo lufsOut;
    bool closed;
};
#endif // MASTER_ME_SHARED_MEMORY
