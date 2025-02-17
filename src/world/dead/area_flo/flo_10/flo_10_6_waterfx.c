#include "flo_10.h"
#include "nu/nusys.h"
#include "model.h"

s32 N(WavePhase) = {
    0
};

// unused wavy distortion effect for edge water -- unclear how it would have been used
EvtScript N(EVS_SetupWaterEffect) = {
    EVT_RETURN
    EVT_END
};

void N(UnkModelFunc000)(s32 x1, s32 y1, s32 x2, s32 y2) {
    s32 i;
    f32 f0;
    s32 n, m;
    u16* img;
    s32 alpha;

    N(WavePhase) += 5;

    if (x1 >= x2 || y1 >= y2) {
        return;
    }

    if (x1 < 0) {
        x1 = 0;
    }
    if (y1 < 0) {
        y1 = 0;
    }
    if (x2 < 0) {
        x2 = 0;
    }
    if (y2 < 0) {
        y2 = 0;
    }

    if (x1 >= SCREEN_WIDTH) {
        x1 = SCREEN_WIDTH - 1;
    }
    if (y1 >= SCREEN_HEIGHT) {
        y1 = SCREEN_HEIGHT - 1;
    }
    if (x2 >= SCREEN_WIDTH) {
        x2 = SCREEN_WIDTH - 1;
    }
    if (y2 >= SCREEN_HEIGHT) {
        y2 = SCREEN_HEIGHT - 1;
    }

    if (x1 == x2 || y1 == y2) {
        return;
    }

    x1 = x1 / 4 * 4;
    x2 = x2 / 4 * 4 + 4;

    n = (y2 - y1) / 6;
    m = (y2 - y1) % 6;
    img = nuGfxCfb_ptr;

    for (i = 0; i < n; i++) {
        alpha = (y1 - 6 * i - 6) * 2;
        if (y1 - 6 * i - 6 >= 0) {
            if (alpha > 255) {
                alpha = 255;
            }
            gDPSetPrimColor(gMasterGfxPos++, 0, 0, 255, 255, 255, alpha);

            //gDPLoadTextureTile(gMasterGfxPos++, osVirtualToPhysical(img), G_IM_FMT_RGBA, G_IM_SIZ_16b,
                            //SCREEN_WIDTH, 6,
                            //x1, y1 - 6 * i - 6, x2 - 1, y1 - 6 * i - 1, 0,
                            //G_TX_WRAP, G_TX_WRAP, 9, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);


            //gDPSetTextureImage(gMasterGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(img));
            {
                Gfx *_g = (Gfx *)(gMasterGfxPos++);

                if ((osVirtualToPhysical(img) % 8) != 0) {
                    osSyncPrintf("GBI Error (aligned 8)  File:%s Line:%d Adrs:%08x \n",
                                 "evt_underwater.c", 83, osVirtualToPhysical(img));
                }
                _g->words.w0 = _SHIFTL(G_SETTIMG, 24, 8) | _SHIFTL(G_IM_FMT_RGBA, 21, 3) |
                        _SHIFTL(G_IM_SIZ_16b, 19, 2) | _SHIFTL((SCREEN_WIDTH)-1, 0, 12);

                _g->words.w1 = (unsigned int)(osVirtualToPhysical(img));
            }
            gDPSetTile(gMasterGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b,
                (((((x2 - 1)-(x1)+1) * G_IM_SIZ_16b_TILE_BYTES)+7)>>3), 0,
                G_TX_LOADTILE, 0 , G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP, 9,
                G_TX_NOLOD);
            gDPLoadSync(gMasterGfxPos++);
            gDPLoadTile(gMasterGfxPos++, G_TX_LOADTILE,
                    (x1)<<G_TEXTURE_IMAGE_FRAC,
                    (y1 - 6 * i - 6)<<G_TEXTURE_IMAGE_FRAC,
                    (x2 - 1)<<G_TEXTURE_IMAGE_FRAC,
                    (y1 - 6 * i - 1)<<G_TEXTURE_IMAGE_FRAC);
            gDPPipeSync(gMasterGfxPos++);
            gDPSetTile(gMasterGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b,
                (((((x2 - 1)-(x1)+1) * G_IM_SIZ_16b_LINE_BYTES)+7)>>3), 0,
                G_TX_RENDERTILE, 0, G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP, 9,
                G_TX_NOLOD);
            gDPSetTileSize(gMasterGfxPos++, G_TX_RENDERTILE,
                    (x1)<<G_TEXTURE_IMAGE_FRAC,
                    (y1 - 6 * i - 6)<<G_TEXTURE_IMAGE_FRAC,
                    (x2 - 1)<<G_TEXTURE_IMAGE_FRAC,
                    (y1 - 6 * i - 1)<<G_TEXTURE_IMAGE_FRAC)
            gSPTextureRectangle(gMasterGfxPos++, x1 * 4, (y1 + i * 6) * 4, x2 * 4, (y1 + i * 6 + 6) * 4,
                                G_TX_RENDERTILE, x1 * 32, (y1 - i * 6) * 32, 1024, (s32)(sin_deg(N(WavePhase) + i * 30) * 500.0f) - 500);
        }
    }

    if (m != 0) {
        alpha = (y1 - 6 * i - 6) * 2;
        if (y1 - 6 * i - 6 >= 0) {
            if (alpha > 255) {
                alpha = 255;
            }
            gDPSetPrimColor(gMasterGfxPos++, 0, 0, 255, 255, 255, alpha);
            //gDPLoadTextureTile(gMasterGfxPos++, osVirtualToPhysical(img), G_IM_FMT_RGBA, G_IM_SIZ_16b,
            //                SCREEN_WIDTH, 6,
            //                x1, y1 - 6 * i - m, x2 - 1, y1 - 6 * i - 1, 0,
            //                G_TX_WRAP, G_TX_WRAP, 9, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            //gDPSetTextureImage(gMasterGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(img));
            {
                Gfx *_g = (Gfx *)(gMasterGfxPos++);

                if ((osVirtualToPhysical(img) % 8) != 0) {
                    osSyncPrintf("GBI Error (aligned 8)  File:%s Line:%d Adrs:%08x \n",
                                 "evt_underwater.c", 107, osVirtualToPhysical(img));
                }
                _g->words.w0 = _SHIFTL(G_SETTIMG, 24, 8) | _SHIFTL(G_IM_FMT_RGBA, 21, 3) |
                        _SHIFTL(G_IM_SIZ_16b, 19, 2) | _SHIFTL((SCREEN_WIDTH)-1, 0, 12);

                _g->words.w1 = (unsigned int)(osVirtualToPhysical(img));
            }
            gDPSetTile(gMasterGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b,
                (((((x2 - 1)-(x1)+1) * G_IM_SIZ_16b_TILE_BYTES)+7)>>3), 0,
                G_TX_LOADTILE, 0 , G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP, 9,
                G_TX_NOLOD);
            gDPLoadSync(gMasterGfxPos++);
            gDPLoadTile(gMasterGfxPos++, G_TX_LOADTILE,
                    (x1)<<G_TEXTURE_IMAGE_FRAC,
                    (y1 - 6 * i - m)<<G_TEXTURE_IMAGE_FRAC,
                    (x2 - 1)<<G_TEXTURE_IMAGE_FRAC,
                    (y1 - 6 * i - 1)<<G_TEXTURE_IMAGE_FRAC);
            gDPPipeSync(gMasterGfxPos++);
            gDPSetTile(gMasterGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b,
                (((((x2 - 1)-(x1)+1) * G_IM_SIZ_16b_LINE_BYTES)+7)>>3), 0,
                G_TX_RENDERTILE, 0, G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP, 9,
                G_TX_NOLOD);
            gDPSetTileSize(gMasterGfxPos++, G_TX_RENDERTILE,
                    (x1)<<G_TEXTURE_IMAGE_FRAC,
                    (y1 - 6 * i - m)<<G_TEXTURE_IMAGE_FRAC,
                    (x2 - 1)<<G_TEXTURE_IMAGE_FRAC,
                    (y1 - 6 * i - 1)<<G_TEXTURE_IMAGE_FRAC)
            gSPTextureRectangle(gMasterGfxPos++, x1 * 4, (y1 + i * 6) * 4, x2 * 4, (y1 + i * 6 + m) * 4,
                                G_TX_RENDERTILE, x1 * 32, (y1 - i * 6) * 32, 1024, -1024);
        }
    }
}

void N(UnkModelFunc001)(void) {
    Camera* camera = &gCameras[gCurrentCameraID];
    Model* model = get_model_from_list_index(get_model_list_index_from_tree_index(MODEL_o40));
    ModelBoundingBox* bb = (ModelBoundingBox*) model->modelNode->propertyList;
    f32 bbHalfX = bb->halfSizeX;
    f32 bbHalfZ = bb->halfSizeZ;
    f32 outX, outY, outZ, outS;
    Gfx* new_var;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f20;
    f32 temp_f22;

    transform_point(camera->perspectiveMatrix,
                    model->center.x - bbHalfX, model->center.y, model->center.z - bbHalfZ, 1.0f,
                    &outX, &outY, &outZ, &outS);

    outX *= 1.0f / outS;
    outY *= -(1.0f / outS);
    outZ *= 1.0f / outS;
    outS = 1.0f / outS;

    if (outS < 0.0f) {
        outX = 0.0f;
        outY = 1.0f;
    }
    temp_f20 = outX;
    temp_f22 = outY;

    transform_point(camera->perspectiveMatrix,
                    model->center.x - bbHalfX, model->center.y, model->center.z + bbHalfZ, 1.0f,
                    &outX, &outY, &outZ, &outS);

    outX *= 1.0f / outS;
    outY *= -(1.0f / outS);
    outZ *= 1.0f / outS;
    outS = 1.0f / outS;

    temp_f24 = temp_f20;
    temp_f26 = temp_f22;
    if (outS < 0.0f) {
        outX = 0.0f;
        outY = 1.0f;
    }

    if (temp_f24 > outX) {
        temp_f24 = outX;
    }

    if (temp_f26 > outY) {
        temp_f26 = outY;
    }

    if (temp_f20 < outX) {
        temp_f20 = outX;
    }

    if (temp_f22 < outY) {
        temp_f22 = outY;
    }

    transform_point(camera->perspectiveMatrix,
                    model->center.x + bbHalfX, model->center.y, model->center.z + bbHalfZ, 1.0f,
                    &outX, &outY, &outZ, &outS);

    outX *= 1.0f / outS;
    outY *= -(1.0f / outS);
    outZ *= 1.0f / outS;
    outS = 1.0f / outS;

    if (outS < 0.0f) {
        outX = 1.0f;
        outY = 1.0f;
    }

    if (temp_f24 > outX) {
        temp_f24 = outX;
    }

    if (temp_f26 > outY) {
        temp_f26 = outY;
    }

    if (temp_f20 < outX) {
        temp_f20 = outX;
    }

    if (temp_f22 < outY) {
        temp_f22 = outY;
    }

    transform_point(camera->perspectiveMatrix,
                    model->center.x + bbHalfX, model->center.y, model->center.z - bbHalfZ, 1.0f,
                    &outX, &outY, &outZ, &outS);

    outX *= 1.0f / outS;
    outY *= -(1.0f / outS);
    outZ *= 1.0f / outS;
    outS = 1.0f / outS;

    if (outS < 0.0f) {
        outX = 1.0f;
        outY = 1.0f;
    }

    if (temp_f24 > outX) {
        temp_f24 = outX;
    }

    if (temp_f26 > outY) {
        temp_f26 = outY;
    }

    if (temp_f20 < outX) {
        temp_f20 = outX;
    }

    if (temp_f22 < outY) {
        temp_f22 = outY;
    }

    if (temp_f24 != temp_f20 || temp_f26 != temp_f22) {
        temp_f24 = ((temp_f24 * camera->viewportW) + camera->viewportW) * 0.5f;
        temp_f26 = ((temp_f26 * camera->viewportH) + camera->viewportH) * 0.5f;
        temp_f20 = ((temp_f20 * camera->viewportW) + camera->viewportW) * 0.5f;
        temp_f22 = ((temp_f22 * camera->viewportH) + camera->viewportH) * 0.5f;

        temp_f24 += camera->viewportStartX;
        temp_f26 += camera->viewportStartY;
        temp_f20 += camera->viewportStartX;
        temp_f22 += camera->viewportStartY;

        gDPSetCycleType(gMasterGfxPos++, G_CYC_1CYCLE);
        gDPSetRenderMode(gMasterGfxPos++, Z_CMP | CVG_DST_CLAMP | ZMODE_OPA | FORCE_BL | G_RM_PASS,
                         Z_CMP | CVG_DST_CLAMP | ZMODE_OPA | FORCE_BL | GBL_c2(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1));

        new_var = gMasterGfxPos++;
        if ((osVirtualToPhysical(nuGfxZBuffer) % 8) != 0) {
            osSyncPrintf("GBI Error (aligned 8)  File:%s Line:%d Adrs:%08x \n",
                         "evt_underwater.c", 175, osVirtualToPhysical(nuGfxZBuffer));
        }
        gDPSetColorImage(new_var, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(nuGfxZBuffer));

        gDPSetCombineLERP(gMasterGfxPos++, 0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, PRIMITIVE, 0, 0, 0, 0);
        gDPSetPrimColor(gMasterGfxPos++, 0, 0, 248, 240, 240, 0);
        gDPPipeSync(gMasterGfxPos++);

        gSPDisplayList(gMasterGfxPos++, model->modelNode->displayData->displayList);
        gDPPipeSync(gMasterGfxPos++);

        new_var = gMasterGfxPos++;
        if ((osVirtualToPhysical(nuGfxCfb_ptr) % 8) != 0) {
            osSyncPrintf("GBI Error (aligned 8)  File:%s Line:%d Adrs:%08x \n",
                         "evt_underwater.c", 186, osVirtualToPhysical(nuGfxCfb_ptr));
        }
        gDPSetColorImage(new_var, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(nuGfxCfb_ptr));

        gDPSetDepthSource(gMasterGfxPos++, G_ZS_PRIM);
        gDPSetPrimDepth(gMasterGfxPos++, 32734, 0);
        gDPSetRenderMode(gMasterGfxPos++, G_RM_ZB_XLU_DECAL, G_RM_ZB_XLU_DECAL2);
        gDPSetTextureFilter(gMasterGfxPos++, G_TF_POINT);
        gDPSetTexturePersp(gMasterGfxPos++, G_TP_NONE);
        gSPTexture(gMasterGfxPos++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        gDPSetTextureLUT(gMasterGfxPos++, G_TT_NONE);
        gDPSetTextureDetail(gMasterGfxPos++, G_TD_CLAMP);
        gDPSetTextureLOD(gMasterGfxPos++, G_TL_TILE);
        gDPSetCombineLERP(gMasterGfxPos++, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE);
        gDPPipeSync(gMasterGfxPos++);

        N(UnkModelFunc000)(temp_f24, temp_f26, temp_f20, temp_f22);

        gDPPipeSync(gMasterGfxPos++);
        gDPSetCycleType(gMasterGfxPos++, G_CYC_2CYCLE);
        gDPSetDepthSource(gMasterGfxPos++, G_ZS_PIXEL);
    }
}

