	.arch armv5te
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"streamerExtension_register.cpp"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.rodata
	.align	2
.LC0:
	.ascii	"STREAMEREXTENSION_VERBOSE\000"
	.align	2
.LC1:
	.ascii	"calling streamerExtension func on main thread: star"
	.ascii	"tStreamingAudio\000"
	.section	.text._ZL24startStreamingAudio_wrapv,"ax",%progbits
	.align	2
	.type	_ZL24startStreamingAudio_wrapv, %function
_ZL24startStreamingAudio_wrapv:
.LFB33:
	.file 1 "C:\\Users\\David\\git\\RadioApp\\UCCSRadio\\streamerExtension\\source\\generic\\streamerExtension_register.cpp"
	.loc 1 28 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
.LCFI0:
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	.loc 1 28 0
	ldr	r4, .L4
.LPIC3:
	add	r4, pc, r4
	.loc 1 29 0
	ldr	r3, .L4+4
.LPIC0:
	add	r3, pc, r3
	mov	r0, r3
	mov	r1, #1
	bl	IwDebugTraceIsChannelOn(PLT)
	mov	r3, r0
	cmp	r3, #0
	moveq	r3, #0
	movne	r3, #1
	and	r3, r3, #255
	cmp	r3, #0
	beq	.L2
	.loc 1 29 0 is_stmt 0 discriminator 1
	ldr	r3, .L4+8
.LPIC1:
	add	r3, pc, r3
	mov	r0, r3
	bl	IwDebugTraceSetTraceChannel(PLT)
	ldr	r3, .L4+12
.LPIC2:
	add	r3, pc, r3
	mov	r0, r3
	bl	IwDebugTraceLinePrintf(PLT)
.L2:
	.loc 1 30 0 is_stmt 1
	ldr	r3, .L4+16
	ldr	r3, [r4, r3]
	mov	r0, r3
	mov	r1, #0
	bl	s3eEdkThreadRunOnOS(PLT)
	mov	r3, r0
	.loc 1 31 0
	mov	r0, r3
	ldmfd	sp!, {r4, pc}
.L5:
	.align	2
.L4:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC3+8)
	.word	.LC0-(.LPIC0+8)
	.word	.LC0-(.LPIC1+8)
	.word	.LC1-(.LPIC2+8)
	.word	startStreamingAudio(GOT)
	.cfi_endproc
.LFE33:
	.size	_ZL24startStreamingAudio_wrapv, .-_ZL24startStreamingAudio_wrapv
	.section	.rodata
	.align	2
.LC2:
	.ascii	"calling streamerExtension func on main thread: stop"
	.ascii	"StreamingAudio\000"
	.section	.text._ZL23stopStreamingAudio_wrapv,"ax",%progbits
	.align	2
	.type	_ZL23stopStreamingAudio_wrapv, %function
_ZL23stopStreamingAudio_wrapv:
.LFB34:
	.loc 1 34 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
.LCFI1:
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	.loc 1 34 0
	ldr	r4, .L9
.LPIC7:
	add	r4, pc, r4
	.loc 1 35 0
	ldr	r3, .L9+4
.LPIC4:
	add	r3, pc, r3
	mov	r0, r3
	mov	r1, #1
	bl	IwDebugTraceIsChannelOn(PLT)
	mov	r3, r0
	cmp	r3, #0
	moveq	r3, #0
	movne	r3, #1
	and	r3, r3, #255
	cmp	r3, #0
	beq	.L7
	.loc 1 35 0 is_stmt 0 discriminator 1
	ldr	r3, .L9+8
.LPIC5:
	add	r3, pc, r3
	mov	r0, r3
	bl	IwDebugTraceSetTraceChannel(PLT)
	ldr	r3, .L9+12
.LPIC6:
	add	r3, pc, r3
	mov	r0, r3
	bl	IwDebugTraceLinePrintf(PLT)
.L7:
	.loc 1 36 0 is_stmt 1
	ldr	r3, .L9+16
	ldr	r3, [r4, r3]
	mov	r0, r3
	mov	r1, #0
	bl	s3eEdkThreadRunOnOS(PLT)
	mov	r3, r0
	.loc 1 37 0
	mov	r0, r3
	ldmfd	sp!, {r4, pc}
.L10:
	.align	2
.L9:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC7+8)
	.word	.LC0-(.LPIC4+8)
	.word	.LC0-(.LPIC5+8)
	.word	.LC2-(.LPIC6+8)
	.word	stopStreamingAudio(GOT)
	.cfi_endproc
.LFE34:
	.size	_ZL23stopStreamingAudio_wrapv, .-_ZL23stopStreamingAudio_wrapv
	.section	.rodata
	.align	2
.LC3:
	.ascii	"calling streamerExtension func on main thread: paus"
	.ascii	"eStreamingAudio\000"
	.section	.text._ZL24pauseStreamingAudio_wrapv,"ax",%progbits
	.align	2
	.type	_ZL24pauseStreamingAudio_wrapv, %function
_ZL24pauseStreamingAudio_wrapv:
.LFB35:
	.loc 1 40 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
.LCFI2:
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	.loc 1 40 0
	ldr	r4, .L14
.LPIC11:
	add	r4, pc, r4
	.loc 1 41 0
	ldr	r3, .L14+4
.LPIC8:
	add	r3, pc, r3
	mov	r0, r3
	mov	r1, #1
	bl	IwDebugTraceIsChannelOn(PLT)
	mov	r3, r0
	cmp	r3, #0
	moveq	r3, #0
	movne	r3, #1
	and	r3, r3, #255
	cmp	r3, #0
	beq	.L12
	.loc 1 41 0 is_stmt 0 discriminator 1
	ldr	r3, .L14+8
.LPIC9:
	add	r3, pc, r3
	mov	r0, r3
	bl	IwDebugTraceSetTraceChannel(PLT)
	ldr	r3, .L14+12
.LPIC10:
	add	r3, pc, r3
	mov	r0, r3
	bl	IwDebugTraceLinePrintf(PLT)
.L12:
	.loc 1 42 0 is_stmt 1
	ldr	r3, .L14+16
	ldr	r3, [r4, r3]
	mov	r0, r3
	mov	r1, #0
	bl	s3eEdkThreadRunOnOS(PLT)
	mov	r3, r0
	.loc 1 43 0
	mov	r0, r3
	ldmfd	sp!, {r4, pc}
.L15:
	.align	2
.L14:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC11+8)
	.word	.LC0-(.LPIC8+8)
	.word	.LC0-(.LPIC9+8)
	.word	.LC3-(.LPIC10+8)
	.word	pauseStreamingAudio(GOT)
	.cfi_endproc
.LFE35:
	.size	_ZL24pauseStreamingAudio_wrapv, .-_ZL24pauseStreamingAudio_wrapv
	.section	.rodata
	.align	2
.LC4:
	.ascii	"calling streamerExtension func on main thread: init"
	.ascii	"AudioStream\000"
	.section	.text._ZL20initAudioStream_wrapPKci,"ax",%progbits
	.align	2
	.type	_ZL20initAudioStream_wrapPKci, %function
_ZL20initAudioStream_wrapPKci:
.LFB36:
	.loc 1 46 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
.LCFI3:
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	sub	sp, sp, #8
.LCFI4:
	.cfi_def_cfa_offset 16
	str	r0, [sp, #4]
	str	r1, [sp, #0]
	.loc 1 46 0
	ldr	r4, .L19
.LPIC15:
	add	r4, pc, r4
	.loc 1 47 0
	ldr	r3, .L19+4
.LPIC12:
	add	r3, pc, r3
	mov	r0, r3
	mov	r1, #1
	bl	IwDebugTraceIsChannelOn(PLT)
	mov	r3, r0
	cmp	r3, #0
	moveq	r3, #0
	movne	r3, #1
	and	r3, r3, #255
	cmp	r3, #0
	beq	.L17
	.loc 1 47 0 is_stmt 0 discriminator 1
	ldr	r3, .L19+8
.LPIC13:
	add	r3, pc, r3
	mov	r0, r3
	bl	IwDebugTraceSetTraceChannel(PLT)
	ldr	r3, .L19+12
.LPIC14:
	add	r3, pc, r3
	mov	r0, r3
	bl	IwDebugTraceLinePrintf(PLT)
.L17:
	.loc 1 48 0 is_stmt 1
	ldr	r3, .L19+16
	ldr	r3, [r4, r3]
	mov	r0, r3
	mov	r1, #2
	ldr	r2, [sp, #4]
	ldr	r3, [sp, #0]
	bl	s3eEdkThreadRunOnOS(PLT)
	mov	r3, r0
	.loc 1 49 0
	mov	r0, r3
	add	sp, sp, #8
	ldmfd	sp!, {r4, pc}
.L20:
	.align	2
.L19:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC15+8)
	.word	.LC0-(.LPIC12+8)
	.word	.LC0-(.LPIC13+8)
	.word	.LC4-(.LPIC14+8)
	.word	initAudioStream(GOT)
	.cfi_endproc
.LFE36:
	.size	_ZL20initAudioStream_wrapPKci, .-_ZL20initAudioStream_wrapPKci
	.section	.rodata
	.align	2
.LC5:
	.ascii	"streamerExtension\000"
	.section	.text._Z28streamerExtensionRegisterExtv,"ax",%progbits
	.align	2
	.global	_Z28streamerExtensionRegisterExtv
	.hidden	_Z28streamerExtensionRegisterExtv
	.type	_Z28streamerExtensionRegisterExtv, %function
_Z28streamerExtensionRegisterExtv:
.LFB37:
	.loc 1 59 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	str	lr, [sp, #-4]!
.LCFI5:
	.cfi_def_cfa_offset 4
	.cfi_offset 14, -4
	sub	sp, sp, #52
.LCFI6:
	.cfi_def_cfa_offset 56
	.loc 1 59 0
	ldr	r2, .L22
.LPIC20:
	add	r2, pc, r2
.LBB2:
	.loc 1 62 0
	ldr	r3, .L22+4
.LPIC16:
	add	r3, pc, r3
	str	r3, [sp, #32]
	.loc 1 63 0
	ldr	r3, .L22+8
.LPIC17:
	add	r3, pc, r3
	str	r3, [sp, #36]
	.loc 1 64 0
	ldr	r3, .L22+12
.LPIC18:
	add	r3, pc, r3
	str	r3, [sp, #40]
	.loc 1 65 0
	ldr	r3, .L22+16
.LPIC19:
	add	r3, pc, r3
	str	r3, [sp, #44]
	.loc 1 70 0
	add	r3, sp, #16
	mov	r1, #0
	str	r1, [r3, #0]
	add	r3, r3, #4
	mov	r1, #0
	str	r1, [r3, #0]
	add	r3, r3, #4
	mov	r1, #0
	str	r1, [r3, #0]
	add	r3, r3, #4
	mov	r1, #0
	str	r1, [r3, #0]
	add	r3, r3, #4
	.loc 1 75 0
	add	r1, sp, #32
	add	r3, sp, #16
	ldr	r0, .L22+20
	ldr	r0, [r2, r0]
	str	r0, [sp, #0]
	ldr	r0, .L22+24
	ldr	r2, [r2, r0]
	str	r2, [sp, #4]
	mov	r2, #0
	str	r2, [sp, #8]
	ldr	r2, .L22+28
.LPIC21:
	add	r2, pc, r2
	mov	r0, r2
	mov	r2, #16
	bl	s3eEdkRegister(PLT)
.LBE2:
	.loc 1 76 0
	add	sp, sp, #52
	ldmfd	sp!, {pc}
.L23:
	.align	2
.L22:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC20+8)
	.word	_ZL24startStreamingAudio_wrapv-(.LPIC16+8)
	.word	_ZL23stopStreamingAudio_wrapv-(.LPIC17+8)
	.word	_ZL24pauseStreamingAudio_wrapv-(.LPIC18+8)
	.word	_ZL20initAudioStream_wrapPKci-(.LPIC19+8)
	.word	_Z21streamerExtensionInitv(GOT)
	.word	_Z26streamerExtensionTerminatev(GOT)
	.word	.LC5-(.LPIC21+8)
	.cfi_endproc
.LFE37:
	.size	_Z28streamerExtensionRegisterExtv, .-_Z28streamerExtensionRegisterExtv
	.section	.text.RegisterExt,"ax",%progbits
	.align	2
	.global	RegisterExt
	.type	RegisterExt, %function
RegisterExt:
.LFB38:
	.loc 1 95 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r3, lr}
.LCFI7:
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	.cfi_offset 14, -4
	.loc 1 96 0
	bl	_Z28streamerExtensionRegisterExtv(PLT)
	.loc 1 97 0
	ldmfd	sp!, {r3, pc}
	.cfi_endproc
.LFE38:
	.size	RegisterExt, .-RegisterExt
	.text
.Letext0:
	.file 2 "c:/marmalade/7.3/s3e/h/s3eTypes.h"
	.file 3 "c:/marmalade/7.3/s3e/edk/h/s3eEdk.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x1c6
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x4
	.4byte	.LASF23
	.4byte	.LASF24
	.4byte	.Ldebug_ranges0+0
	.4byte	0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF3
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF4
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF6
	.uleb128 0x4
	.4byte	.LASF10
	.byte	0x2
	.byte	0x54
	.4byte	0x4c
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x5
	.4byte	.LASF11
	.byte	0x4
	.byte	0x2
	.byte	0xcf
	.4byte	0x8c
	.uleb128 0x6
	.4byte	.LASF8
	.sleb128 0
	.uleb128 0x6
	.4byte	.LASF9
	.sleb128 1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF11
	.byte	0x2
	.byte	0xd3
	.4byte	0x73
	.uleb128 0x7
	.byte	0x4
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF12
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF13
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF14
	.uleb128 0x8
	.byte	0x4
	.4byte	0xb4
	.uleb128 0x9
	.4byte	0xa7
	.uleb128 0xa
	.4byte	.LASF15
	.byte	0x3
	.2byte	0x282
	.4byte	0xc5
	.uleb128 0x8
	.byte	0x4
	.4byte	0xcb
	.uleb128 0xb
	.4byte	0x97
	.uleb128 0xc
	.4byte	.LASF16
	.byte	0x1
	.byte	0x1b
	.4byte	0x8c
	.4byte	.LFB33
	.4byte	.LFE33
	.4byte	.LLST0
	.byte	0x1
	.uleb128 0xc
	.4byte	.LASF17
	.byte	0x1
	.byte	0x21
	.4byte	0x8c
	.4byte	.LFB34
	.4byte	.LFE34
	.4byte	.LLST1
	.byte	0x1
	.uleb128 0xc
	.4byte	.LASF18
	.byte	0x1
	.byte	0x27
	.4byte	0x8c
	.4byte	.LFB35
	.4byte	.LFE35
	.4byte	.LLST2
	.byte	0x1
	.uleb128 0xd
	.4byte	.LASF25
	.byte	0x1
	.byte	0x2d
	.4byte	0x8c
	.4byte	.LFB36
	.4byte	.LFE36
	.4byte	.LLST3
	.byte	0x1
	.4byte	0x150
	.uleb128 0xe
	.ascii	"ip\000"
	.byte	0x1
	.byte	0x2d
	.4byte	0xae
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0xf
	.4byte	.LASF19
	.byte	0x1
	.byte	0x2d
	.4byte	0x4c
	.byte	0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x10
	.byte	0x1
	.4byte	.LASF26
	.byte	0x1
	.byte	0x3a
	.4byte	.LASF27
	.4byte	.LFB37
	.4byte	.LFE37
	.4byte	.LLST4
	.byte	0x1
	.4byte	0x194
	.uleb128 0x11
	.4byte	.LBB2
	.4byte	.LBE2
	.uleb128 0x12
	.4byte	.LASF20
	.byte	0x1
	.byte	0x3d
	.4byte	0x194
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x12
	.4byte	.LASF21
	.byte	0x1
	.byte	0x46
	.4byte	0x1a4
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.byte	0
	.uleb128 0x13
	.4byte	0x97
	.4byte	0x1a4
	.uleb128 0x14
	.4byte	0xa0
	.byte	0x3
	.byte	0
	.uleb128 0x13
	.4byte	0x4c
	.4byte	0x1b4
	.uleb128 0x14
	.4byte	0xa0
	.byte	0x3
	.byte	0
	.uleb128 0x15
	.byte	0x1
	.4byte	.LASF28
	.byte	0x1
	.byte	0x5e
	.4byte	.LFB38
	.4byte	.LFE38
	.4byte	.LLST5
	.byte	0x1
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x15
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LFB33
	.4byte	.LCFI0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI0
	.4byte	.LFE33
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LFB34
	.4byte	.LCFI1
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI1
	.4byte	.LFE34
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LLST2:
	.4byte	.LFB35
	.4byte	.LCFI2
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI2
	.4byte	.LFE35
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LLST3:
	.4byte	.LFB36
	.4byte	.LCFI3
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI3
	.4byte	.LCFI4
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI4
	.4byte	.LFE36
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	0
	.4byte	0
.LLST4:
	.4byte	.LFB37
	.4byte	.LCFI5
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI5
	.4byte	.LCFI6
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI6
	.4byte	.LFE37
	.2byte	0x2
	.byte	0x7d
	.sleb128 56
	.4byte	0
	.4byte	0
.LLST5:
	.4byte	.LFB38
	.4byte	.LCFI7
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI7
	.4byte	.LFE38
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x44
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB33
	.4byte	.LFE33-.LFB33
	.4byte	.LFB34
	.4byte	.LFE34-.LFB34
	.4byte	.LFB35
	.4byte	.LFE35-.LFB35
	.4byte	.LFB36
	.4byte	.LFE36-.LFB36
	.4byte	.LFB37
	.4byte	.LFE37-.LFB37
	.4byte	.LFB38
	.4byte	.LFE38-.LFB38
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LFB33
	.4byte	.LFE33
	.4byte	.LFB34
	.4byte	.LFE34
	.4byte	.LFB35
	.4byte	.LFE35
	.4byte	.LFB36
	.4byte	.LFE36
	.4byte	.LFB37
	.4byte	.LFE37
	.4byte	.LFB38
	.4byte	.LFE38
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF17:
	.ascii	"stopStreamingAudio_wrap\000"
.LASF8:
	.ascii	"S3E_RESULT_SUCCESS\000"
.LASF1:
	.ascii	"signed char\000"
.LASF0:
	.ascii	"unsigned char\000"
.LASF23:
	.ascii	"C:\\Users\\David\\git\\RadioApp\\UCCSRadio\\streame"
	.ascii	"rExtension\\source\\generic\\streamerExtension_regi"
	.ascii	"ster.cpp\000"
.LASF7:
	.ascii	"long unsigned int\000"
.LASF2:
	.ascii	"short unsigned int\000"
.LASF27:
	.ascii	"_Z28streamerExtensionRegisterExtv\000"
.LASF10:
	.ascii	"intptr_t\000"
.LASF4:
	.ascii	"unsigned int\000"
.LASF21:
	.ascii	"flags\000"
.LASF6:
	.ascii	"long long unsigned int\000"
.LASF9:
	.ascii	"S3E_RESULT_ERROR\000"
.LASF13:
	.ascii	"sizetype\000"
.LASF26:
	.ascii	"streamerExtensionRegisterExt\000"
.LASF5:
	.ascii	"long long int\000"
.LASF25:
	.ascii	"initAudioStream_wrap\000"
.LASF14:
	.ascii	"char\000"
.LASF20:
	.ascii	"funcPtrs\000"
.LASF28:
	.ascii	"RegisterExt\000"
.LASF19:
	.ascii	"port\000"
.LASF3:
	.ascii	"short int\000"
.LASF16:
	.ascii	"startStreamingAudio_wrap\000"
.LASF18:
	.ascii	"pauseStreamingAudio_wrap\000"
.LASF12:
	.ascii	"long int\000"
.LASF24:
	.ascii	"c:\\\\Users\\\\David\\\\git\\\\RadioApp\\\\UCCSRadi"
	.ascii	"o\\\\streamerExtension\\\\build_streamerextension_a"
	.ascii	"ndroid_linux_scons_arm\000"
.LASF11:
	.ascii	"s3eResult\000"
.LASF15:
	.ascii	"s3eEdkThreadFunc\000"
.LASF22:
	.ascii	"GNU C++ 4.7\000"
	.ident	"GCC: (GNU) 4.7"
	.section	.note.GNU-stack,"",%progbits
