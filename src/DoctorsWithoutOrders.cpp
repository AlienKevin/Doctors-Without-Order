#include "DoctorsWithoutOrders.h"
#include "map.h"
#include <climits>
#include <iostream>
using namespace std;

/* * * * Doctors Without Orders * * * */
bool canAllPatientsBeSeen(Vector<Doctor> &doctors,
                          Vector<Patient> &patients,
                          Map<string, Set<string>>& schedule);
bool canAllPatientsBeSeenHelper(Vector<Doctor> &doctors,
                          Vector<Patient> &patients,
                          Map<string, Set<string>>& schedule);

/**
 * Given a list of doctors and a list of patients, determines whether all the patients can
 * be seen. If so, this function fills in the schedule outparameter with a map from doctors
 * to the set of patients that doctor would see.
 *
 * @param doctors  The list of the doctors available to work.
 * @param patients The list of the patients that need to be seen.
 * @param schedule An outparameter that will be filled in with the schedule, should one exist.
 * @return Whether or not a schedule was found.
 */
bool canAllPatientsBeSeen(Vector<Doctor> &doctors,
                          Vector<Patient> &patients,
                          Map<string, Set<string>>& schedule) {
    int totalHoursFree = 0;
    for (int i = 0; i < doctors.size(); i ++) {
        totalHoursFree += doctors[i].hoursFree;
    }
    int totalHoursNeeded = 0;
    for (int i = 0; i < patients.size(); i ++) {
        totalHoursNeeded += patients[i].hoursNeeded;
    }
    if (totalHoursNeeded > totalHoursFree) {
        return false;
    } else {
        return canAllPatientsBeSeenHelper(doctors, patients, schedule);
    }
}

bool canAllPatientsBeSeenHelper(Vector<Doctor> &doctors,
                          Vector<Patient> &patients,
                          Map<string, Set<string>>& schedule) {
    if (patients.size() == 0) {
        return true;
    }
    bool findMatch = false;
    for (int i = 0; i < patients.size(); i ++) {
        for (int j = 0; j < doctors.size(); j ++) {
            Patient patient = patients[i];
            if (doctors[j].hoursFree >= patients[i].hoursNeeded) {
                // change
                doctors[j].hoursFree -= patients[i].hoursNeeded;
                patients.remove(i);
                // explore
                if (canAllPatientsBeSeen(doctors, patients, schedule)) {
                    schedule[doctors[j].name].add(patient.name);
                    findMatch = true;
                }
                // un-change
                patients.insert(i, patient);
                doctors[j].hoursFree += patient.hoursNeeded;

                if (findMatch) {
                    return true;
                }
            }
        }
    }
    return false;
}
