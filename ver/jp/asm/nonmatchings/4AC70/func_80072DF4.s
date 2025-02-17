.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel func_80072DF4
/* 4E1F4 80072DF4 27BDFFE0 */  addiu     $sp, $sp, -0x20
/* 4E1F8 80072DF8 3C038007 */  lui       $v1, %hi(gGameStatusPtr)
/* 4E1FC 80072DFC 2463417C */  addiu     $v1, $v1, %lo(gGameStatusPtr)
/* 4E200 80072E00 AFBF0018 */  sw        $ra, 0x18($sp)
/* 4E204 80072E04 AFB10014 */  sw        $s1, 0x14($sp)
/* 4E208 80072E08 AFB00010 */  sw        $s0, 0x10($sp)
/* 4E20C 80072E0C 8C620000 */  lw        $v0, ($v1)
/* 4E210 80072E10 A04000AA */  sb        $zero, 0xaa($v0)
/* 4E214 80072E14 8C620000 */  lw        $v0, ($v1)
/* 4E218 80072E18 0080882D */  daddu     $s1, $a0, $zero
/* 4E21C 80072E1C A4400086 */  sh        $zero, 0x86($v0)
/* 4E220 80072E20 A440008C */  sh        $zero, 0x8c($v0)
/* 4E224 80072E24 0C00AAF0 */  jal       func_8002ABC0
/* 4E228 80072E28 A0400070 */   sb       $zero, 0x70($v0)
/* 4E22C 80072E2C 0C04A0B2 */  jal       func_801282C8
/* 4E230 80072E30 00000000 */   nop
/* 4E234 80072E34 0C0B0C77 */  jal       func_802C31DC
/* 4E238 80072E38 00000000 */   nop
/* 4E23C 80072E3C 0C00B6E1 */  jal       func_8002DB84
/* 4E240 80072E40 00000000 */   nop
/* 4E244 80072E44 0C044512 */  jal       func_80111448
/* 4E248 80072E48 0000202D */   daddu    $a0, $zero, $zero
/* 4E24C 80072E4C 0C048D0D */  jal       func_80123434
/* 4E250 80072E50 00000000 */   nop
/* 4E254 80072E54 0C049770 */  jal       func_80125DC0
/* 4E258 80072E58 00000000 */   nop
/* 4E25C 80072E5C 0C00E05F */  jal       func_8003817C
/* 4E260 80072E60 00000000 */   nop
/* 4E264 80072E64 0C05186C */  jal       func_801461B0
/* 4E268 80072E68 00000000 */   nop
/* 4E26C 80072E6C 0C0529CC */  jal       func_8014A730
/* 4E270 80072E70 00000000 */   nop
/* 4E274 80072E74 0C046BD5 */  jal       func_8011AF54
/* 4E278 80072E78 00000000 */   nop
/* 4E27C 80072E7C 0C05343C */  jal       func_8014D0F0
/* 4E280 80072E80 00000000 */   nop
/* 4E284 80072E84 0C052BAA */  jal       func_8014AEA8
/* 4E288 80072E88 00000000 */   nop
/* 4E28C 80072E8C 0C04F48E */  jal       func_8013D238
/* 4E290 80072E90 00000000 */   nop
/* 4E294 80072E94 0C01CAC4 */  jal       func_80072B10
/* 4E298 80072E98 00000000 */   nop
/* 4E29C 80072E9C 0C00F830 */  jal       func_8003E0C0
/* 4E2A0 80072EA0 00000000 */   nop
/* 4E2A4 80072EA4 0C0457B2 */  jal       func_80115EC8
/* 4E2A8 80072EA8 24040001 */   addiu    $a0, $zero, 1
/* 4E2AC 80072EAC 0C016653 */  jal       func_8005994C
/* 4E2B0 80072EB0 00000000 */   nop
/* 4E2B4 80072EB4 0C037F0C */  jal       func_800DFC30
/* 4E2B8 80072EB8 00000000 */   nop
/* 4E2BC 80072EBC 0C04A221 */  jal       func_80128884
/* 4E2C0 80072EC0 00000000 */   nop
/* 4E2C4 80072EC4 0C04D85C */  jal       func_80136170
/* 4E2C8 80072EC8 00000000 */   nop
/* 4E2CC 80072ECC 0C039CD0 */  jal       func_800E7340
/* 4E2D0 80072ED0 00000000 */   nop
/* 4E2D4 80072ED4 0C039E35 */  jal       func_800E78D4
/* 4E2D8 80072ED8 00000000 */   nop
/* 4E2DC 80072EDC 0C04D85C */  jal       func_80136170
/* 4E2E0 80072EE0 00000000 */   nop
/* 4E2E4 80072EE4 3C05437F */  lui       $a1, 0x437f
/* 4E2E8 80072EE8 0C04F38E */  jal       func_8013CE38
/* 4E2EC 80072EEC 24040009 */   addiu    $a0, $zero, 9
/* 4E2F0 80072EF0 3C108011 */  lui       $s0, %hi(D_8010F450)
/* 4E2F4 80072EF4 2610F450 */  addiu     $s0, $s0, %lo(D_8010F450)
/* 4E2F8 80072EF8 2E220005 */  sltiu     $v0, $s1, 5
/* 4E2FC 80072EFC 1040002D */  beqz      $v0, .L80072FB4
/* 4E300 80072F00 00111080 */   sll      $v0, $s1, 2
/* 4E304 80072F04 3C01800A */  lui       $at, %hi(D_8009A558)
/* 4E308 80072F08 00220821 */  addu      $at, $at, $v0
/* 4E30C 80072F0C 8C22A558 */  lw        $v0, %lo(D_8009A558)($at)
/* 4E310 80072F10 00400008 */  jr        $v0
/* 4E314 80072F14 00000000 */   nop
/* 4E318 80072F18 0C01CB43 */  jal       func_80072D0C
/* 4E31C 80072F1C 24112700 */   addiu    $s1, $zero, 0x2700
/* 4E320 80072F20 0000202D */  daddu     $a0, $zero, $zero
/* 4E324 80072F24 0801CBF0 */  j         .L80072FC0
/* 4E328 80072F28 A200000A */   sb       $zero, 0xa($s0)
/* 4E32C 80072F2C 0C01CB43 */  jal       func_80072D0C
/* 4E330 80072F30 24112701 */   addiu    $s1, $zero, 0x2701
/* 4E334 80072F34 0000202D */  daddu     $a0, $zero, $zero
/* 4E338 80072F38 24020009 */  addiu     $v0, $zero, 9
/* 4E33C 80072F3C 0801CBF0 */  j         .L80072FC0
/* 4E340 80072F40 A2020012 */   sb       $v0, 0x12($s0)
/* 4E344 80072F44 0C01CB43 */  jal       func_80072D0C
/* 4E348 80072F48 24112702 */   addiu    $s1, $zero, 0x2702
/* 4E34C 80072F4C 0000202D */  daddu     $a0, $zero, $zero
/* 4E350 80072F50 3C038007 */  lui       $v1, %hi(gGameStatusPtr)
/* 4E354 80072F54 8C63417C */  lw        $v1, %lo(gGameStatusPtr)($v1)
/* 4E358 80072F58 24020004 */  addiu     $v0, $zero, 4
/* 4E35C 80072F5C A2020012 */  sb        $v0, 0x12($s0)
/* 4E360 80072F60 906200AA */  lbu       $v0, 0xaa($v1)
/* 4E364 80072F64 34420002 */  ori       $v0, $v0, 2
/* 4E368 80072F68 0801CBF0 */  j         .L80072FC0
/* 4E36C 80072F6C A06200AA */   sb       $v0, 0xaa($v1)
/* 4E370 80072F70 0C01CB43 */  jal       func_80072D0C
/* 4E374 80072F74 24112703 */   addiu    $s1, $zero, 0x2703
/* 4E378 80072F78 0000202D */  daddu     $a0, $zero, $zero
/* 4E37C 80072F7C 24020006 */  addiu     $v0, $zero, 6
/* 4E380 80072F80 0801CBF0 */  j         .L80072FC0
/* 4E384 80072F84 A2020012 */   sb       $v0, 0x12($s0)
/* 4E388 80072F88 0C01CB43 */  jal       func_80072D0C
/* 4E38C 80072F8C 24112704 */   addiu    $s1, $zero, 0x2704
/* 4E390 80072F90 0000202D */  daddu     $a0, $zero, $zero
/* 4E394 80072F94 3C038007 */  lui       $v1, %hi(gGameStatusPtr)
/* 4E398 80072F98 8C63417C */  lw        $v1, %lo(gGameStatusPtr)($v1)
/* 4E39C 80072F9C 24020002 */  addiu     $v0, $zero, 2
/* 4E3A0 80072FA0 A2020012 */  sb        $v0, 0x12($s0)
/* 4E3A4 80072FA4 906200AA */  lbu       $v0, 0xaa($v1)
/* 4E3A8 80072FA8 34420004 */  ori       $v0, $v0, 4
/* 4E3AC 80072FAC 0801CBF0 */  j         .L80072FC0
/* 4E3B0 80072FB0 A06200AA */   sb       $v0, 0xaa($v1)
.L80072FB4:
/* 4E3B4 80072FB4 0C01CB43 */  jal       func_80072D0C
/* 4E3B8 80072FB8 24112700 */   addiu    $s1, $zero, 0x2700
/* 4E3BC 80072FBC 24040002 */  addiu     $a0, $zero, 2
.L80072FC0:
/* 4E3C0 80072FC0 3C038007 */  lui       $v1, %hi(gGameStatusPtr)
/* 4E3C4 80072FC4 2463417C */  addiu     $v1, $v1, %lo(gGameStatusPtr)
/* 4E3C8 80072FC8 8C620000 */  lw        $v0, ($v1)
/* 4E3CC 80072FCC A0400074 */  sb        $zero, 0x74($v0)
/* 4E3D0 80072FD0 8C630000 */  lw        $v1, ($v1)
/* 4E3D4 80072FD4 24020001 */  addiu     $v0, $zero, 1
/* 4E3D8 80072FD8 A062007C */  sb        $v0, 0x7c($v1)
/* 4E3DC 80072FDC 2C820005 */  sltiu     $v0, $a0, 5
/* 4E3E0 80072FE0 10400049 */  beqz      $v0, .L80073108
/* 4E3E4 80072FE4 00041080 */   sll      $v0, $a0, 2
/* 4E3E8 80072FE8 3C01800A */  lui       $at, %hi(D_8009A570)
/* 4E3EC 80072FEC 00220821 */  addu      $at, $at, $v0
/* 4E3F0 80072FF0 8C22A570 */  lw        $v0, %lo(D_8009A570)($at)
/* 4E3F4 80072FF4 00400008 */  jr        $v0
/* 4E3F8 80072FF8 00000000 */   nop
/* 4E3FC 80072FFC 3C03800B */  lui       $v1, %hi(D_800B0EF0)
/* 4E400 80073000 24630EF0 */  addiu     $v1, $v1, %lo(D_800B0EF0)
/* 4E404 80073004 3C048007 */  lui       $a0, %hi(gGameStatusPtr)
/* 4E408 80073008 2484417C */  addiu     $a0, $a0, %lo(gGameStatusPtr)
/* 4E40C 8007300C A0600004 */  sb        $zero, 4($v1)
/* 4E410 80073010 8C850000 */  lw        $a1, ($a0)
/* 4E414 80073014 24020001 */  addiu     $v0, $zero, 1
/* 4E418 80073018 A0620005 */  sb        $v0, 5($v1)
/* 4E41C 8007301C A0600006 */  sb        $zero, 6($v1)
/* 4E420 80073020 90A200AA */  lbu       $v0, 0xaa($a1)
/* 4E424 80073024 34420010 */  ori       $v0, $v0, 0x10
/* 4E428 80073028 A0A200AA */  sb        $v0, 0xaa($a1)
/* 4E42C 8007302C 8C830000 */  lw        $v1, ($a0)
/* 4E430 80073030 906200AA */  lbu       $v0, 0xaa($v1)
/* 4E434 80073034 34420020 */  ori       $v0, $v0, 0x20
/* 4E438 80073038 A06200AA */  sb        $v0, 0xaa($v1)
/* 4E43C 8007303C 8C830000 */  lw        $v1, ($a0)
/* 4E440 80073040 906200AA */  lbu       $v0, 0xaa($v1)
/* 4E444 80073044 34420040 */  ori       $v0, $v0, 0x40
/* 4E448 80073048 0801CC42 */  j         .L80073108
/* 4E44C 8007304C A06200AA */   sb       $v0, 0xaa($v1)
/* 4E450 80073050 3C03800B */  lui       $v1, %hi(D_800B0EF0)
/* 4E454 80073054 24630EF0 */  addiu     $v1, $v1, %lo(D_800B0EF0)
/* 4E458 80073058 24020001 */  addiu     $v0, $zero, 1
/* 4E45C 8007305C A0620004 */  sb        $v0, 4($v1)
/* 4E460 80073060 92040001 */  lbu       $a0, 1($s0)
/* 4E464 80073064 3C058007 */  lui       $a1, %hi(gGameStatusPtr)
/* 4E468 80073068 8CA5417C */  lw        $a1, %lo(gGameStatusPtr)($a1)
/* 4E46C 8007306C 0801CC25 */  j         .L80073094
/* 4E470 80073070 24020004 */   addiu    $v0, $zero, 4
/* 4E474 80073074 3C03800B */  lui       $v1, %hi(D_800B0EF0)
/* 4E478 80073078 24630EF0 */  addiu     $v1, $v1, %lo(D_800B0EF0)
/* 4E47C 8007307C 24020001 */  addiu     $v0, $zero, 1
/* 4E480 80073080 A0620004 */  sb        $v0, 4($v1)
/* 4E484 80073084 92040000 */  lbu       $a0, ($s0)
/* 4E488 80073088 3C058007 */  lui       $a1, %hi(gGameStatusPtr)
/* 4E48C 8007308C 8CA5417C */  lw        $a1, %lo(gGameStatusPtr)($a1)
/* 4E490 80073090 24020002 */  addiu     $v0, $zero, 2
.L80073094:
/* 4E494 80073094 A0620005 */  sb        $v0, 5($v1)
/* 4E498 80073098 A0640006 */  sb        $a0, 6($v1)
/* 4E49C 8007309C 90A200AA */  lbu       $v0, 0xaa($a1)
/* 4E4A0 800730A0 34420010 */  ori       $v0, $v0, 0x10
/* 4E4A4 800730A4 0801CC42 */  j         .L80073108
/* 4E4A8 800730A8 A0A200AA */   sb       $v0, 0xaa($a1)
/* 4E4AC 800730AC 3C03800B */  lui       $v1, %hi(D_800B0EF0)
/* 4E4B0 800730B0 24630EF0 */  addiu     $v1, $v1, %lo(D_800B0EF0)
/* 4E4B4 800730B4 24020001 */  addiu     $v0, $zero, 1
/* 4E4B8 800730B8 A0620004 */  sb        $v0, 4($v1)
/* 4E4BC 800730BC 3C048007 */  lui       $a0, %hi(gGameStatusPtr)
/* 4E4C0 800730C0 8C84417C */  lw        $a0, %lo(gGameStatusPtr)($a0)
/* 4E4C4 800730C4 24020006 */  addiu     $v0, $zero, 6
/* 4E4C8 800730C8 A0620005 */  sb        $v0, 5($v1)
/* 4E4CC 800730CC 908200AA */  lbu       $v0, 0xaa($a0)
/* 4E4D0 800730D0 0801CC41 */  j         .L80073104
/* 4E4D4 800730D4 34420020 */   ori      $v0, $v0, 0x20
/* 4E4D8 800730D8 3C03800B */  lui       $v1, %hi(D_800B0EF0)
/* 4E4DC 800730DC 24630EF0 */  addiu     $v1, $v1, %lo(D_800B0EF0)
/* 4E4E0 800730E0 24020002 */  addiu     $v0, $zero, 2
/* 4E4E4 800730E4 A0620004 */  sb        $v0, 4($v1)
/* 4E4E8 800730E8 3C048007 */  lui       $a0, %hi(gGameStatusPtr)
/* 4E4EC 800730EC 8C84417C */  lw        $a0, %lo(gGameStatusPtr)($a0)
/* 4E4F0 800730F0 24020001 */  addiu     $v0, $zero, 1
/* 4E4F4 800730F4 A0620005 */  sb        $v0, 5($v1)
/* 4E4F8 800730F8 A0600006 */  sb        $zero, 6($v1)
/* 4E4FC 800730FC 908200AA */  lbu       $v0, 0xaa($a0)
/* 4E500 80073100 34420040 */  ori       $v0, $v0, 0x40
.L80073104:
/* 4E504 80073104 A08200AA */  sb        $v0, 0xaa($a0)
.L80073108:
/* 4E508 80073108 0000202D */  daddu     $a0, $zero, $zero
/* 4E50C 8007310C 3C05F840 */  lui       $a1, 0xf840
/* 4E510 80073110 34A56299 */  ori       $a1, $a1, 0x6299
/* 4E514 80073114 0C0B2026 */  jal       func_802C8098
/* 4E518 80073118 24060001 */   addiu    $a2, $zero, 1
/* 4E51C 8007311C 2404FFFF */  addiu     $a0, $zero, -1
/* 4E520 80073120 3C02800B */  lui       $v0, %hi(D_800B0EF0)
/* 4E524 80073124 24420EF0 */  addiu     $v0, $v0, %lo(D_800B0EF0)
/* 4E528 80073128 A0400007 */  sb        $zero, 7($v0)
/* 4E52C 8007312C 0C01CB2B */  jal       func_80072CAC
/* 4E530 80073130 A0400010 */   sb       $zero, 0x10($v0)
/* 4E534 80073134 3C038007 */  lui       $v1, %hi(gGameStatusPtr)
/* 4E538 80073138 8C63417C */  lw        $v1, %lo(gGameStatusPtr)($v1)
/* 4E53C 8007313C 0220202D */  daddu     $a0, $s1, $zero
/* 4E540 80073140 906200AA */  lbu       $v0, 0xaa($v1)
/* 4E544 80073144 3C05800A */  lui       $a1, %hi(D_8009A630)
/* 4E548 80073148 24A5A630 */  addiu     $a1, $a1, %lo(D_8009A630)
/* 4E54C 8007314C 34420001 */  ori       $v0, $v0, 1
/* 4E550 80073150 A06200AA */  sb        $v0, 0xaa($v1)
/* 4E554 80073154 8CA20000 */  lw        $v0, ($a1)
/* 4E558 80073158 2403FFF7 */  addiu     $v1, $zero, -9
/* 4E55C 8007315C 00431024 */  and       $v0, $v0, $v1
/* 4E560 80073160 0C01CB1C */  jal       func_80072C70
/* 4E564 80073164 ACA20000 */   sw       $v0, ($a1)
/* 4E568 80073168 8FBF0018 */  lw        $ra, 0x18($sp)
/* 4E56C 8007316C 8FB10014 */  lw        $s1, 0x14($sp)
/* 4E570 80073170 8FB00010 */  lw        $s0, 0x10($sp)
/* 4E574 80073174 03E00008 */  jr        $ra
/* 4E578 80073178 27BD0020 */   addiu    $sp, $sp, 0x20
/* 4E57C 8007317C 00000000 */  nop
