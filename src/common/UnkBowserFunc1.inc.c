#include "common.h"
#include "sprite.h"

#ifndef BOWSER_LARGE
#define BOWSER_FLAG_TOCHECK ACTOR_EVENT_FLAG_ENCHANTED
#else
#define BOWSER_FLAG_TOCHECK ACTOR_EVENT_FLAG_80000
#endif

ApiStatus N(UnkBowserFunc1)(Evt* script, s32 isInitialCall) {
    Actor* actor = get_actor(script->owner1.actorID);
    ActorPart* part;
    s32 i, j;
    u8 sp20[20];
    u8 sp38[20];
    u8 sp50[20];
    s32 colorRGBA;
    s32 temp;
    s32 lol;

    if (actor == NULL) {
        return ApiStatus_DONE2;
    }

    part = get_actor_part(actor, 1);

    if (isInitialCall) {
        script->functionTemp[1] = 0;
        script->functionTemp[2] = 0;
        script->functionTemp[0] = 0;

        for (i = 0; i < 10; i++) {
            func_802DE780(part->unk_84, i, 17, 20, 0, 0, 255, 0);
        }
    }

    script->functionTemp[1] += 10;
    if (script->functionTemp[1] >= 360) {
        script->functionTemp[1] %= 360;
    }

    for (j = 0; j < 20; j++) {
        sp20[j] = (cosine(script->functionTemp[1] + j * 25 + 120) + 1.0) * 56.0;
        sp38[j] = (cosine(script->functionTemp[1] + j * 25 + 60) + 1.0) * 56.0;
        sp50[j] = (cosine(script->functionTemp[1] + j * 25 + 180) + 1.0) * 56.0;
    }

    if (part->eventFlags & BOWSER_FLAG_TOCHECK) {

        for (j = 0; j < 20; j++) {
            colorRGBA = sp20[j] << 0x18 | sp38[j] << 0x10 | sp50[j] << 8 | 0xFF;
            for (i = 0; i < 10; i++) {
                func_802DE780(part->unk_84, i, 12, j, colorRGBA, 0, 255, 0);
            }
        }
        return ApiStatus_BLOCK;
    } else {
        s32 opacity = 255;
        for (j = 0; j < 20; j++) {
            colorRGBA = 255;
            for (i = 0; i < 10; i++) {
                // TODO find better match for opacity
                func_802DE780(part->unk_84, i, 12, j, colorRGBA, 0, opacity & 0xFFFF, 0);
            }
        }
        script->functionTemp[1] = 0;
        script->functionTemp[2] = 0;
        script->functionTemp[0] = 0;
        return ApiStatus_BLOCK;
    }
}
