#include "common.h"
#include "effects_internal.h"

void windy_leaves_init(EffectInstance* effect);
void windy_leaves_update(EffectInstance* effect);
void windy_leaves_render(EffectInstance* effect);
void windy_leaves_appendGfx(void* effect);

void windy_leaves_main(s32 type, f32 arg1, f32 arg2, f32 arg3) {
    EffectBlueprint bp;
    EffectBlueprint* bpPtr = &bp;
    EffectInstance* effect;
    WindyLeavesFXData* part;
    s32 numParts;
    s32 i;

    bp.init = windy_leaves_init;
    bp.update = windy_leaves_update;
    bp.renderWorld = windy_leaves_render;
    bp.unk_00 = 0;
    bp.unk_14 = NULL;
    bp.effectID = EFFECT_WINDY_LEAVES;
    
    numParts = 5;
    effect = shim_create_effect_instance(bpPtr);
    effect->numParts = numParts;
    effect->data.windyLeaves = part = shim_general_heap_malloc(numParts * sizeof(*part));
    ASSERT(part != NULL);

    part->type = type;
    part->unk_04.x = arg1;
    part->unk_04.y = arg2;
    part->unk_04.z = arg3;
    part->unk_28 = 100;
    part->unk_2C = 0;
    part->alpha = 0;

    part++;
    for (i = 1; i < numParts; i++, part++) {
        s32 temp_s0_2 = func_E0200000(50);
        s32 temp_s1 = func_E0200000(20);
        s32 temp_s2 = func_E0200000(360);
        s32 temp_v0_2 = func_E0200000(100);
        part->unk_04.x = temp_s0_2 + 75;
        part->unk_04.y = temp_s1 + 70;
        part->unk_04.z = 0;
        part->unk_18 = temp_s2;
        part->unk_20 = 360 - temp_s2;

        switch (type) {
            case 0:
                part->unk_10 = 0.0f;
                part->unk_14 = 0.0f;
                part->unk_34 = 0;
                part->unk_30 = -3.0f;;
                part->unk_38 = 3.0f;
                part->unk_1C = (f32)temp_v0_2 * 0.1;
                break;
            case 1:
                part->unk_10 = 0.0f;
                part->unk_14 = 0.0f;
                part->unk_34 = 0;
                part->unk_30 = -6.0f;
                part->unk_38 = 6.0f;
                part->unk_1C = 2.0 * ((f32)temp_v0_2 * 0.1);
                break;
            case 2:
                part->unk_1C = 2.0 * ((f32)temp_v0_2 * 0.1);
                part->unk_10 = -part->unk_04.x * (shim_rand_int(10) * 0.008 + 0.05);
                part->unk_14 = -part->unk_04.y * (shim_rand_int(10) * 0.008 + 0.05);
                break;
            default:
                break;
        }
    }
}

void windy_leaves_init(EffectInstance* effect) {
}

void windy_leaves_update(EffectInstance* effect) {
    WindyLeavesFXData* part = effect->data.windyLeaves;
    f32 temp_f0_2;
    f32 temp_f4;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_a1;
    s32 i;
    s32 temp;
    s32 temp2;

    part->unk_28--;
    part->unk_2C++;
    if (part->unk_28 < 0) {
        shim_remove_effect(effect);
        return;
    }
    temp_a1 = part->unk_2C;
    temp_v0 = part->unk_28;
    temp = part->type;
    if (temp_a1 < 10) {
        part->alpha += (255 - part->alpha) * 0.3;
    }
    if (temp_v0 < 10) {
        part->alpha *= 0.8;
    }

    part++;
    switch (temp) {
        case 0:
            for (i = 1; i < effect->numParts; i++, part++) {
                f32 temp3 = (shim_sin_deg(2.0f * part->unk_18) * 0.2);
                part->unk_14 += -0.05f;
                part->unk_10 += temp3;
                if (temp == 0) {
                    part->unk_10 *= 0.94;
                    part->unk_14 *= shim_sin_deg(part->unk_18) * 0.05 + 0.95;
                } else {
                    part->unk_14 += -0.05f;
                    part->unk_10 *= 0.92;
                }
                part->unk_1C += func_E0200044(50, temp_a1 + i * 20) - 25;
                part->unk_18 += shim_sin_deg(part->unk_1C) * 10.0f;
                part->unk_20 += shim_cos_deg(part->unk_1C * 0.5) * 10.0f;
                part->unk_04.x += part->unk_10;
                part->unk_04.y += part->unk_14;
                if (part->unk_04.y < 30.0f) {
                    if (part->unk_04.x > -200.0f) {
                        part->unk_30 -= 0.4;
                    } else {
                        part->unk_30 += 0.4;
                    }
                    if (part->unk_04.z > 0.0f) {
                        part->unk_38 -= 0.4;
                    } else {
                        part->unk_38 += 0.4;
                    }
                    part->unk_30 *= 0.98;
                    part->unk_38 *= 0.98;
                    part->unk_14 *= 0.98;
                } else {
                    if(part->unk_04.x > 0.0f) {
                        part->unk_30 -= 0.4;
                    } else {
                        part->unk_30 += 0.4;
                    }
                    if (part->unk_04.z > 0.0f){
                        part->unk_38 -= 0.4;
                    } else {
                        part->unk_38 += 0.4;
                    }
                    part->unk_30 *= 0.98;
                    part->unk_38 *= 0.98;
                }
                part->unk_04.x += part->unk_30;
                part->unk_04.y += part->unk_34;
                part->unk_04.z += part->unk_38;
            }
            break;
        case 1:
            for (i = 1; i < effect->numParts; i++, part++) {
                part->unk_10 += (f32)(shim_sin_deg(2.0f * part->unk_18) * 0.2 * 2.0);
                part->unk_14 += -0.05f;
                part->unk_10 *= 0.8464;
                part->unk_14 += -0.05f;
                part->unk_1C += func_E0200044(50, temp_a1 + i * 20) - 25;
                part->unk_18 += shim_sin_deg(part->unk_1C) * 10.0f;
                part->unk_20 += shim_cos_deg(part->unk_1C * 0.5) * 10.0f;
                part->unk_04.x += part->unk_10;
                part->unk_04.y += part->unk_14;
                if (part->unk_04.y < 30.0f) {
                    if (part->unk_04.x > -200.0f) {
                        part->unk_30 -= 0.8;
                    } else {
                        part->unk_30 += 0.8;
                    }
                    if (part->unk_04.z > 0.0f) {
                        part->unk_38 -= 0.8;
                    } else {
                        part->unk_38 += 0.8;
                    }
                    part->unk_30 *= 0.9603999999999999;
                    part->unk_38 *= 0.9603999999999999;
                    part->unk_14 *= 0.9603999999999999;
                } else {
                    if (part->unk_04.x > 0.0f){
                        part->unk_30 -= 0.8;
                    } else {
                        part->unk_30 += 0.8;
                    }
                    if (part->unk_04.z > 0.0f){
                        part->unk_38 -= 0.8;
                    } else {
                        part->unk_38 += 0.8;
                    }
                    part->unk_30 *= 0.9603999999999999;
                    part->unk_38 *= 0.9603999999999999;
                }
                part->unk_04.x += part->unk_30;
                part->unk_04.y += part->unk_34;
                part->unk_04.z += part->unk_38;
            }
            break;
        case 2:
            for (i = 1; i < effect->numParts; i++, part++) {
                part->unk_1C += func_E0200044(50,  temp_a1 + i * 20) - 25;
                part->unk_18 += shim_sin_deg(part->unk_1C) * 10.0f;
                part->unk_20 += shim_cos_deg(part->unk_1C * 0.5) * 10.0f;
                part->unk_04.x += part->unk_10;
                part->unk_04.y += part->unk_14;
            }
            break;
    }
}

void windy_leaves_render(EffectInstance* effect) {
    RenderTask renderTask;
    RenderTask* retTask;

    renderTask.appendGfx = windy_leaves_appendGfx;
    renderTask.appendGfxArg = effect;
    renderTask.distance = 0;
    renderTask.renderMode = RENDER_MODE_2D;

    retTask = shim_queue_render_task(&renderTask);
    retTask->renderMode |= RENDER_TASK_FLAG_2;
}

extern Gfx D_09001180_33E790[];
extern Gfx D_09001258_33E868[];
extern Gfx D_09001280_33E890[];

void windy_leaves_appendGfx(void* effect) {
    WindyLeavesFXData* part;
    Gfx* phi_s7;
    s32 i;
    Matrix4f sp18;
    Matrix4f sp58;
    Matrix4f sp98;

    part = ((EffectInstance*)effect)->data.windyLeaves;
    phi_s7 = D_09001280_33E890;
    if (part->type == 0) {
        phi_s7 = D_09001258_33E868;
    }

    gSPSegment(gMasterGfxPos++, 0x09, OS_K0_TO_PHYSICAL(((EffectInstance*)effect)->graphics->data));
    gSPDisplayList(gMasterGfxPos++, D_09001180_33E790);
    gDPSetPrimColor(gMasterGfxPos++, 0, 0, 20, 100, 20, part->alpha);
    shim_guTranslateF(sp18, part->unk_04.x, part->unk_04.y, part->unk_04.z);
    shim_guRotateF(sp58, -gCameras[gCurrentCameraID].currentYaw, 0.0f, 1.0f, 0.0f);
    shim_guMtxCatF(sp58, sp18, sp98);

    part++;
    for (i = 1; i < ((EffectInstance*)effect)->numParts; i++, part++) {
        shim_guTranslateF(sp58, part->unk_04.x, part->unk_04.y, part->unk_04.z);
        shim_guMtxCatF(sp58, sp98, sp18);
        shim_guRotateF(sp58, part->unk_18, 0.0f, 0.0f, 1.0f);
        shim_guMtxCatF(sp58, sp18, sp18);
        shim_guRotateF(sp58, part->unk_20, 0.0f, 1.0f, 0.0f);
        shim_guMtxCatF(sp58, sp18, sp18);
        shim_guMtxF2L(sp18, &gDisplayContext->matrixStack[gMatrixListPos]);
        gSPMatrix(gMasterGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        gSPDisplayList(gMasterGfxPos++, phi_s7);
        gSPPopMatrix(gMasterGfxPos++, G_MTX_MODELVIEW);
    }
}

