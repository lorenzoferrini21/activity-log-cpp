#include <gtest/gtest.h>

#include "../Time.h"
#include "../Activity.h"
#include "../DailyLog.h"
#include "../Category.h"

#include <vector>
#include <cstdio> // remove()


TEST(SanityTest, BasicAssertion) {
EXPECT_EQ(1, 1);
}

//TEST TIME

TEST(TimeTest, ConstructorAndToMinutes) {
    Time t(10, 30);
    EXPECT_EQ(t.toMinutes(), 630);
}

TEST(TimeTest, ComparisonOperators) {
    Time t1(9, 0);
    Time t2(10, 0);
    Time t3(10,0);

    EXPECT_TRUE(t1 < t2);
    EXPECT_FALSE(t2 < t1);
    EXPECT_TRUE(t3 <= t2);
}

TEST(TimeTest, ToStringFormat) {
    Time t(8, 5);
    EXPECT_EQ(t.toString(), "08:05");
}

//TEST ACTIVITY

TEST(ActivityTest, DurationInMinutes) {
    Activity a("Studio",
               Time(9, 0),
               Time(11, 0),
               Category::Study);

    EXPECT_EQ(a.durationMinutes(), 120);
}

TEST(ActivityTest, ToStringContainsInfo) {
    Activity a("Pranzo",
               Time(13, 0),
               Time(14, 0),
               Category::Leisure);

    std::string s = a.toString();

    EXPECT_NE(s.find("Pranzo"), std::string::npos);
    EXPECT_NE(s.find("13:00"), std::string::npos);
    EXPECT_NE(s.find("14:00"), std::string::npos);
}

// TEST DAILYLOG

TEST(DailyLogTest, ActivitiesAreSortedChronologically) {
    DailyLog log("2026-02-06");

    log.addActivity(Activity("B",
                             Time(11, 0),
                             Time(13, 0),
                             Category::Work));

    log.addActivity(Activity("A",
                             Time(8, 0),
                             Time(9, 0),
                             Category::Study));

    log.addActivity(Activity("C",
                             Time(12, 0),
                             Time(14, 0),
                             Category::Study));

    const auto& activities = log.getActivities();

    EXPECT_EQ(activities[0].getDescription(), "A");
    EXPECT_EQ(activities[1].getDescription(), "B");
    EXPECT_TRUE(log.hasOverlaps());
    EXPECT_EQ(log.getTotalTimeByCategory(Category::Study), 180);
    auto gaps = log.getGapsInMinutes();

    ASSERT_EQ(gaps.size(), 1);
    EXPECT_EQ(gaps[0], 120);
}


TEST(DailyLogTest, SaveAndLoadFromFile) {
    const std::string filename = "test_log.txt";

    {
        DailyLog log("2026-02-06");
        log.addActivity(Activity("Studio",
                                 Time(9, 0),
                                 Time(10, 0),
                                 Category::Study));
        log.saveToFile(filename);
    }

    DailyLog loaded = DailyLog::loadFromFile(filename);
    const auto& activities = loaded.getActivities();

    ASSERT_EQ(activities.size(), 1);
    EXPECT_EQ(activities[0].getDescription(), "Studio");

    std::remove(filename.c_str()); // pulizia
}







