/*****************************************************************************
 * Copyright 2011 Broadcom Corporation.  All rights reserved.
 *
 * Unless you and Broadcom execute a separate written software license
 * agreement governing use of this software, this software is licensed to you
 * under the terms of the GNU General Public License version 2, available at
 * http://www.broadcom.com/licenses/GPLv2.php (the "GPL").
 *
 * Notwithstanding the above, under no circumstances may you combine this
 * software in any way with any other Broadcom software provided under a
 * license other than the GPL, without Broadcom's express prior written
 * consent.
 *****************************************************************************/

#ifndef _VC_AUDIO_DEFS_H_
#define _VC_AUDIO_DEFS_H_

#define VC_AUDIOSERV_MIN_VER 1
#define VC_AUDIOSERV_VER 2

/* FourCC code used for VCHI connection */
#define VC_AUDIO_SERVER_NAME  MAKE_FOURCC("AUDS")

/* Maximum message length */
#define VC_AUDIO_MAX_MSG_LEN  (sizeof( VC_AUDIO_MSG_T ))

/*
 *  List of screens that are currently supported
 *  All message types supported for HOST->VC direction
 */

enum vc_audio_msg_type {
	VC_AUDIO_MSG_TYPE_RESULT, // Generic result
	VC_AUDIO_MSG_TYPE_COMPLETE, // Generic result
	VC_AUDIO_MSG_TYPE_CONFIG, // Configure audio
	VC_AUDIO_MSG_TYPE_CONTROL, // Configure audio
	VC_AUDIO_MSG_TYPE_OPEN, // Configure audio
	VC_AUDIO_MSG_TYPE_CLOSE, // Configure audio
	VC_AUDIO_MSG_TYPE_START, // Configure audio
	VC_AUDIO_MSG_TYPE_STOP, // Configure audio
	VC_AUDIO_MSG_TYPE_WRITE, // Configure audio
	VC_AUDIO_MSG_TYPE_MAX
};

/* configure the audio */

struct vc_audio_config {
	u32 channels;
	u32 samplerate;
	u32 bps;
};

struct vc_audio_control {
	u32 volume;
	u32 dest;
};

struct vc_audio_open {
	u32 dummy;
};

struct vc_audio_close {
	u32 dummy;
};

struct vc_audio_start {
	u32 dummy;
};

struct vc_audio_stop {
	u32 draining;
};

/* configure the write audio samples */
struct vc_audio_write {
	u32 count; // in bytes
#if defined(CONFIG_64BIT)
	u32 callbackl;
	u32 callbackh;
#else
	void *callback;
	void *cookie;
#endif
	s16 silence;
	s16 max_packet;
};

/* Generic result for a request (VC->HOST) */
struct vc_audio_result {
	s32 success; // Success value
};

/* Generic result for a request (VC->HOST) */
struct vc_audio_complete {
	s32 count; // Success value
#if defined(CONFIG_64BIT)
	u32 callbackl;
	u32 callbackh;
#else
	void *callback;
	void *cookie;
#endif
};

/* Message header for all messages in HOST->VC direction */
struct vc_audio_msg {
	s32 type; /* Message type (VC_AUDIO_MSG_TYPE) */
	union {
		struct vc_audio_config config;
		struct vc_audio_control control;
		struct vc_audio_open open;
		struct vc_audio_close close;
		struct vc_audio_start start;
		struct vc_audio_stop stop;
		struct vc_audio_write write;
		struct vc_audio_result result;
		struct vc_audio_complete complete;
	} u;
};

#endif /* _VC_AUDIO_DEFS_H_ */
