#ifndef CORE_RENSA_TRACKER_RENSA_COMPOSITE_TRACKER_H_
#define CORE_RENSA_TRACKER_RENSA_COMPOSITE_TRACKER_H_

#include "core/rensa_tracker.h"

template<typename Tracker1, typename Tracker2>
class RensaCompositeTracker {
public:
    RensaCompositeTracker(Tracker1* tracker1, Tracker2* tracker2) :
        tracker1_(tracker1), tracker2_(tracker2)
    {
    }

    void trackCoef(int nthChain, int numErasedPuyo, int longBonusCoef, int colorBonusCoef)
    {
        tracker1_->trackCoef(nthChain, numErasedPuyo, longBonusCoef, colorBonusCoef);
        tracker2_->trackCoef(nthChain, numErasedPuyo, longBonusCoef, colorBonusCoef);
    }

    void trackVanish(int nthChain, const FieldBits& vanishedColorPuyoBits, const FieldBits& vanishedOjamaPuyoBits)
    {
        tracker1_->trackVanish(nthChain, vanishedColorPuyoBits, vanishedOjamaPuyoBits);
        tracker2_->trackVanish(nthChain, vanishedColorPuyoBits, vanishedOjamaPuyoBits);
    }

    void trackDrop(FieldBits blender, FieldBits leftOnes, FieldBits rightOnes)
    {
        tracker1_->trackDrop(blender, leftOnes, rightOnes);
        tracker2_->trackDrop(blender, leftOnes, rightOnes);
    }

private:
    Tracker1* tracker1_;
    Tracker2* tracker2_;
};

#endif // CORE_RENSA_TRACKER_RENSA_COMPOSITE_TRACKER_H_
