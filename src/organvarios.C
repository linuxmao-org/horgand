/*
  horgand - a organ software

 organvarios.C  -  miscelaneous functions
  Copyright (C) 2003-2004 Josep Andreu (Holborn)
  Author: Josep Andreu

 This program is free software; you can redistribute it and/or modify
 it under the terms of version 2 of the GNU General Public License
 as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License (version 2) for more details.

 You should have received a copy of the GNU General Public License
 (version2)  along with this program; if not, write to the Free Software
 Foundation,
 Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

*/


#include "Holrgan.h"
#include <math.h>
// Identify Chords


void HOR::Get_Chord()
{
    int i, j;
    int anote[POLY];
    int onote[POLY];
    int nnotes = 0;
    int posi = 0;
    int baja, ubaja;
    int pafuera = 0;
    int busca = 0;
    int dist1, dist2, dist3, dist4;
    char AName[16];


    chord = 0;
    for (i = 0; i <= POLY; i++) {
        if ((note_active[i] == 1) && (rnote[i] < 60)) {
            anote[nnotes] = rnote[i];
            nnotes++;
        }
    }


    if ((nnotes > 5) || (nnotes < 3))
        return;

    while (posi < nnotes) {
        baja = 400;

        for (i = 0; i < nnotes; i++) {
            if (anote[i] <= baja) {
                onote[posi] = anote[i];
                ubaja = baja;
                baja = anote[i];
                pafuera = i;
            }
        }
        baja = ubaja;
        anote[pafuera] = 1000;
        posi++;
    }


    if (nnotes == 3) {

        dist1 = onote[1] - onote[0];
        dist2 = onote[2] - onote[1];

        j = 0;

        while (busca == 0)

        {
            j++;
            if ((Chord3[j].dist1 == dist1) && (Chord3[j].dist2 == dist2)) {
                busca = 1;
                chord = j;
                chord_type = Chord3[j].type;
                break;
            }

            if (j > 14)
                break;
        }

        if (chord != 0) {

            int elke = onote[Chord3[chord].fund - 1];
            fundamental = elke % 12;
            sprintf(AName, "%s%s", NC[fundamental].Nom, Chord3[chord].Nom);

            if (strcmp(AName, NameChord) != 0) {
                strcpy(NameChord, AName);
                changeNameChord = 1;
            }
        }
        return;
    }

    if (nnotes == 4) {

        dist1 = onote[1] - onote[0];
        dist2 = onote[2] - onote[1];
        dist3 = onote[3] - onote[2];
        j = 0;

        while (busca == 0)

        {
            j++;
            if ((Chord4[j].dist1 == dist1) && (Chord4[j].dist2 == dist2) &&
                (Chord4[j].dist3 == dist3)) {
                busca = 1;
                chord = j;
                chord_type = Chord4[j].type;
                break;
            }

            if (j > 46)
                break;
        }

        if (chord != 0) {
            int elke = onote[Chord4[chord].fund - 1];
            fundamental = elke % 12;
            sprintf(AName, "%s%s", NC[fundamental].Nom, Chord4[chord].Nom);
            if (strcmp(AName, NameChord) != 0) {
                strcpy(NameChord, AName);
                changeNameChord = 1;
            }
        }
        return;
    }

    if (nnotes == 5) {

        dist1 = onote[1] - onote[0];
        dist2 = onote[2] - onote[1];
        dist3 = onote[3] - onote[2];
        dist4 = onote[4] - onote[3];
        j = 0;

        while (busca == 0)

        {
            j++;
            if ((Chord5[j].dist1 == dist1) && (Chord5[j].dist2 == dist2) &&
                (Chord5[j].dist3 == dist3) && (Chord5[j].dist4 == dist4)) {
                busca = 1;
                chord = j;
                chord_type = Chord5[j].type;
                break;
            }

            if (j > 9)
                break;
        }

        if (chord != 0) {
            int elke = onote[Chord5[chord].fund - 1];
            fundamental = elke % 12;
            sprintf(AName, "%s%s", NC[fundamental].Nom, Chord5[chord].Nom);
            if (strcmp(AName, NameChord) != 0) {
                strcpy(NameChord, AName);
                changeNameChord = 1;
            }
        }
    }
};

// Init Some Vars

void HOR::Put_Period()
{
    PERIOD2 = PERIOD * 2;
    PERIOD4 = PERIOD * 4;
    PERIOD8 = PERIOD * 8;
};

void HOR::New_Bank()
{
    int j;

    New();
    for (j = 1; j <= 32; j++)
        Banco[j] = a[0];
};


// Reset vars to New Preset

void HOR::New()
{
    int i;

    for (i = 1; i <= 10; i++) {
        a[0].Operator[i].harmonic_fine = 0.0;
        a[0].Operator[i].volumen = 0.0;
        a[0].Operator[i].marimba = 0;
        a[0].Operator[i].wave = 1;
    }

    a[0].Operator[1].harmonic = 1;
    a[0].Operator[2].harmonic = 3;
    a[0].Operator[3].harmonic = 4;
    a[0].Operator[4].harmonic = 5;
    a[0].Operator[5].harmonic = 7;
    a[0].Operator[6].harmonic = 8;
    a[0].Operator[7].harmonic = 11;
    a[0].Operator[8].harmonic = 14;
    a[0].Operator[9].harmonic = 19;
    a[0].Operator[10].harmonic = 22;


    a[0].E_Delay_On = 0;
    a[0].Delay_Delay = 0;
    a[0].Delay_Volume = 0;
    a[0].Pitch_LFO_Speed = 0;
    a[0].Pitch_LFO_Delay = 0;
    a[0].Rotary_LFO_Speed = 0;
    a[0].LFOpitch = 0;
    a[0].modulation = .99;
    a[0].organ_transpose = 0;
    a[0].E_Rotary_On = 0;
    pitch = 0;
    pedal = 0;
    Master_Volume = 0.70;
    a[0].Organ_Master_Volume = 0.70;
    a[0].detune = 0;
    a[0].scaling = 0;
    a[0].Chorus_Volume = 0.60;
    a[0].E_Chorus_On = 0;
    a[0].Chorus_LFO_Speed = 0;
    a[0].Chorus_LFO_Amplitude = 0;
    a[0].Chorus_Delay = 0;
    a[0].Reverb_Preset = 1;
    a[0].E_Reverb_On = 0;
    bzero(a[0].Name, sizeof(a[0].Name));
    a[0].nombre = a[0].Name;
    a[0].Normalize[1] = 1.0;
    a[0].Normalize[2] = 1.0;
    a[0].Normalize[3] = 1.0;
    a[0].Normalize[4] = 1.0;
    a[0].Normalize[5] = 1.0;
    a[0].Normalize[6] = 1.0;
    a[0].Normalize[7] = 1.0;
    a[0].Normalize[8] = 1.0;
    a[0].Normalize[9] = .22;
    a[0].Normalize[10] = .2;
    a[0].Normalize[11] = .166;
    a[0].Normalize[12] = .142;
    a[0].Normalize[13] = .133;
    a[0].Normalize[14] = .125;
    a[0].Normalize[15] = .111;
    a[0].Normalize[16] = .1;
    a[0].Normalize[17] = 0.095;
    a[0].Normalize[18] = 0.090;
    a[0].Normalize[19] = 0.083;
    a[0].Normalize[20] = 0.076;
    a[0].Normalize[21] = 0.071;
    a[0].Normalize[22] = .066;
    a[0].attack = 0.003;
    u_attack = 1.0 / a[0].attack;
    a[0].decay = 0.28;
    u_decay = 1.0 / a[0].decay;
    a[0].sustain = 0.8;
    a[0].p_attack = 0.0002;
    u_p_attack = 1.0 / a[0].p_attack;
    a[0].p_decay = 0.077;
    u_p_decay = 1.0 / a[0].p_decay;
    p_release = 0.1;
    u_p_release = 1.0 / p_release;
    a[0].c_attack = 0.0001;
    a[0].c_decay = 0.003;
    u_c_attack = 1.0 / a[0].c_attack;
    u_c_decay = 1.0 / a[0].c_decay;
    a[0].Click_Vol = .2;
    a[0].Click2_Vol = .09;
    a[0].Click_Vol1 = .23;
    a[0].Click_Vol2 = .04;
    a[0].Click_Freq = 360;
    a[0].Click_Freq2 = 6712;
    a[0].Click = 0;
    a[0].Rotary_LFO_Amplitude = 9980;
    a[0].Speed_Sync = 0;
    a[0].LFO_Wave = 1;
    a[0].Chorus_Wave = 1;
    a[0].Rotary_Wave = 1;
}


// Puts Undo

void HOR::MUndo()
{
    UndoCount = UndoCount - 1;
    if (UndoCount == -1)
        UndoCount = 95;
    PonDATA_Undo(UndoCount);
};

void HOR::PonDATA_Undo(int UndoCount)
{
    a[0] = Undo[UndoCount];
};


// Puts Redo

void HOR::MRedo()
{
    UndoCount = UndoCount + 1;
    if (UndoCount == 95)
        UndoCount = 0;
    PonDATA_Undo(UndoCount);
};


// Refresh Undo/Redo Buffer when something is edited

void HOR::MActu()
{
    UndoCount++;
    if (UndoCount == 95)
        UndoCount = 0;
    Undo[UndoCount] = a[0];
    syncadsr();
};


// Put Undo/Redo buffers on Loaded Preset State for Compare

void HOR::PutPrim()
{
    Prim[1] = a[0];
};


// Put the Loaded Preset for Compare


void HOR::MGetPrim()
{
    a[0] = Prim[1];
};


void HOR::Get_Combi_t(int i)
{
    Banco[i] = a[0];
};


void HOR::Put_Combi_t(int i)
{
    a[0] = Banco[i];
    PutReverb(a[0].Reverb_Preset);
    syncadsr();
    Prim[1] = Banco[i];
};


void HOR::syncadsr()
{

    int i;

    u_attack = 1.0 / a[0].attack;
    u_decay = 1.0 / a[0].decay;
    u_p_attack = 1.0 / a[0].p_attack;
    u_p_decay = 1.0 / a[0].p_decay;
    u_c_attack = 1.0 / a[0].c_attack;
    u_c_decay = 1.0 / a[0].c_decay;


    total_vol = .1;
    organ_master = a[0].Organ_Master_Volume * .1;


    for (i = 1; i < 11; i++)

    {
        p_op[i] = pitch_Operator(i, 0);
        p_op2[i] = pitch_Operator2(i, 0);
        total_vol += a[0].Operator[i].volumen * a[0].Normalize[a[0].Operator[i].harmonic];
    }

    organ_master = a[0].Organ_Master_Volume / total_vol;

    Click_sFreq = a[0].Click_Freq * D_PI_to_SAMPLE_RATE;
    Click_2sFreq = a[0].Click_Freq2 * D_PI_to_SAMPLE_RATE;
};


void HOR::PutReverb(int i)
{

    int j;

    Clean_Buffer_Effects();

    switch (i) {
    case 1:
        Reverb_Time = 16;
        Reverb_Volume = 0.65;
        Reverb_Diffussion = 0.14;

        break;

    case 2:
        Reverb_Time = 18;
        Reverb_Volume = 0.65;
        Reverb_Diffussion = 0.14;
        break;

    case 3:
        Reverb_Time = 20;
        Reverb_Volume = 0.65;
        Reverb_Diffussion = 0.16;
        break;

    case 4:
        Reverb_Time = 22;
        Reverb_Volume = 0.65;
        Reverb_Diffussion = 0.16;
        break;

    case 5:
        Reverb_Time = 24;
        Reverb_Volume = 0.65;
        Reverb_Diffussion = 0.16;
        break;

    case 6:
        Reverb_Time = 26;
        Reverb_Volume = 0.65;
        Reverb_Diffussion = 0.16;

    case 7:
        Reverb_Time = 30;
        Reverb_Volume = 0.65;
        Reverb_Diffussion = 0.16;
        break;

    case 8:
        Reverb_Time = 34;
        Reverb_Volume = 0.65;
        Reverb_Diffussion = 0.16;
        break;
    }

    for (j = 0; j < 16; j++) {
        a_combl[j] = (Reverb_Time * combl[j]);
        a_combr[j] = (Reverb_Time * combr[j]);
    }
};
