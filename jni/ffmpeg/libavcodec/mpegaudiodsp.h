/*
 * This file is part of Libav.
 *
 * Libav is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * Libav is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Libav; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVCODEC_MPEGAUDIODSP_H
#define AVCODEC_MPEGAUDIODSP_H

#include <stdint.h>

typedef struct MPADSPContext {
    void (*apply_window_float)(float *synth_buf, float *window,
                               int *dither_state, float *samples, int incr);
    void (*apply_window_fixed)(int32_t *synth_buf, int32_t *window,
                               int *dither_state, int16_t *samples, int incr);
    void (*dct32_float)(float *dst, const float *src);
    void (*dct32_fixed)(int *dst, const int *src);
    void (*imdct36_float)(float *out, float *buf, float *in, float *win);
    void (*imdct36_fixed)(int *out, int *buf, int *in, int *win);
} MPADSPContext;

void ff_mpadsp_init(MPADSPContext *s);

extern int32_t ff_mpa_synth_window_fixed[];
extern float   ff_mpa_synth_window_float[];

void ff_mpa_synth_filter_fixed(MPADSPContext *s,
                               int32_t *synth_buf_ptr, int *synth_buf_offset,
                               int32_t *window, int *dither_state,
                               int16_t *samples, int incr,
                               int32_t *sb_samples);

void ff_mpa_synth_filter_float(MPADSPContext *s,
                               float *synth_buf_ptr, int *synth_buf_offset,
                               float *window, int *dither_state,
                               float *samples, int incr,
                               float *sb_samples);

void ff_mpadsp_init_arm(MPADSPContext *s);
void ff_mpadsp_init_mmx(MPADSPContext *s);
void ff_mpadsp_init_altivec(MPADSPContext *s);

void ff_mpa_synth_init_float(float *window);
void ff_mpa_synth_init_fixed(int32_t *window);

void ff_mpadsp_apply_window_float(float *synth_buf, float *window,
                                  int *dither_state, float *samples,
                                  int incr);
void ff_mpadsp_apply_window_fixed(int32_t *synth_buf, int32_t *window,
                                  int *dither_state, int16_t *samples,
                                  int incr);

void ff_imdct36_fixed(int *out, int *buf, int *in, int *win);
void ff_imdct36_float(float *out, float *buf, float *in, float *win);

#endif /* AVCODEC_MPEGAUDIODSP_H */
