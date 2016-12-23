#include "decision_planner.h"

#include <atomic>
#include <gtest/gtest.h>

#include "base/unit.h"
#include "core/core_field.h"
#include "core/kumipuyo_seq.h"

using namespace std;

Unit unitMidEvaluator(const RefPlan&) { return Unit(); }

template<typename Callback>
void runTest(const CoreField& field, const KumipuyoSeq& kumipuyoSeq, int maxDepth, Callback f)
{
    PlayerState me;
    PlayerState enemy;
    me.field = field;
    me.seq = kumipuyoSeq;

    DecisionPlanner<Unit> planner(unitMidEvaluator, f);
    planner.iterate(100, field, kumipuyoSeq, me, enemy, maxDepth);
}

TEST(DecisionPlannerTest, iterate)
{
    CoreField field("  YY  ");
    KumipuyoSeq kumipuyoSeq("RRBB");

    CoreField expected(
        "..RR.."
        "BBYY..");

    bool found = false;
    auto f = [&](const RefPlan& plan, const Unit&) {
        if (expected != plan.field())
            return;

        found = true;
        int expectedFrames = 0;
        expectedFrames += field.framesToDropNext(Decision(3, 1));
        expectedFrames += FRAMES_PREPARING_NEXT;
        expectedFrames += field.framesToDropNext(Decision(2, 3));
        EXPECT_EQ(expectedFrames, plan.totalFrames());

        vector<Decision> expectedDecisions { Decision(3, 1), Decision(2, 3) };
        EXPECT_EQ(expectedDecisions, plan.decisions());
    };

    runTest(field, kumipuyoSeq, 2, f);
    EXPECT_TRUE(found);
}

TEST(DecisionPlannerTest, iterateWithRensa)
{
    CoreField field(
        "  RR  ");
    KumipuyoSeq seq("RRBB");

    bool found = false;
    vector<Decision> expectedDecisions { Decision(3, 2) };

    auto f = [&](const RefPlan& plan, const Unit&) {
        if (expectedDecisions != plan.decisions())
            return;

        found = true;

        EXPECT_EQ(1, plan.rensaResult().chains);
        EXPECT_EQ(40, plan.rensaResult().score);
        EXPECT_EQ(FRAMES_VANISH_ANIMATION, plan.rensaResult().frames);
        EXPECT_TRUE(plan.rensaResult().quick);

        EXPECT_EQ(FRAMES_TO_DROP_FAST[10] + FRAMES_GROUNDING + FRAMES_VANISH_ANIMATION, plan.totalFrames());
        EXPECT_EQ(0, plan.framesToIgnite());

        EXPECT_EQ(0, plan.numChigiri());
    };

    runTest(field, seq, 2, f);
    EXPECT_TRUE(found);
}

TEST(DecisionPlannerTest, numChigiri)
{
    CoreField field("  O   ");
    KumipuyoSeq seq("RRRR");

    vector<Decision> expectedDecisions { Decision(3, 1), Decision(3, 1) };

    bool found = false;
    auto f = [&](const RefPlan& plan, const Unit&) {
        if (expectedDecisions != plan.decisions())
            return;

        found = true;
        EXPECT_EQ(2, plan.numChigiri());
    };

    runTest(field, seq, 2, f);
    EXPECT_TRUE(found);
}
