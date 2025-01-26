#ifndef PATIANT_HPP
#define PATIANT_HPP

#include <ctime>

enum Priority {
    LOW_PRIORITY = 0,
    MEDIUM_PRIORITY = 1,
    HIGH_PRIORITY = 2
};

enum Status{
        ARRIVING = 0,
        TRIAGE_QUEUE = 1,
        TRIAGE = 2,
        ATTENDANCE_QUEUE = 3,
        ATTENDANCE = 4,
        MEDICAL_HOSPITALIZATION_QUEUE = 5,
        MEDICAL_HOSPITALIZATION = 6,
        TEST_QUEUE = 7,
        TEST = 8,
        EXAM_QUEUE = 9,
        EXAM = 10,
        MEDICATION_QUEUE = 11,
        MEDICATION = 12,
        DISCHARGE = 13
};

struct Patiant{
        int id;
        bool discharge;
        struct tm *entry_date;
        int urgency; //vai de 0 a 2 (priority)
        int num_hosp_mesures;
        int num_tests;
        int num_exams;
        int num_medications;
        int status = 0; //vai de 0 a 13 (Status)
        double time_in_queue, time_in_treatment, total_time; 
        double entry_queue;

        Patiant();
        ~Patiant();
        //void Initialize(int id, bool discharge, int year, int month, int day, int hour, int urgency, int hosp_mesures, int tests, int exams, int medications);
        void ConfigDate(int month, int year);
        void PrintStatistics();
        double GetPatiantTime(int id);
        int GetProcedureTime();
};

#endif