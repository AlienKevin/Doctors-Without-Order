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
    Vector<Doctor> copiedDoctors = doctors;
    Vector<Patient> copiedPatients = patients;
    return canAllPatientsBeSeenHelper(copiedDoctors, copiedPatients, schedule);
}

bool canAllPatientsBeSeenHelper(Vector<Doctor> &doctors,
                                Vector<Patient> &patients,
                                Map<string, Set<string>>& schedule) {
//    cout << "Calling canAllPatientsBeSeenHelper..." << endl;
    if (patients.size() == 0) {
        return true;
    }
    for (int i = 0; i < patients.size(); i ++) {
        for (int j = 0; j < doctors.size(); j ++) {
            Patient patient = patients[i];
            if (doctors[j].hoursFree >= patients[i].hoursNeeded) {
                // change
                doctors[j].hoursFree -= patients[i].hoursNeeded;
                patients.remove(i);
                // explore
                if (canAllPatientsBeSeenHelper(doctors, patients, schedule)) {
//                    cout << "All patients can be seen!" << endl;
//                    cout << doctors << endl;
//                    cout << patients << endl;
                    schedule[doctors[j].name].add(patient.name);
                    return true;
                }
                // un-change
                patients.insert(i, patient);
                doctors[j].hoursFree += patient.hoursNeeded;
            }
        }
    }
//    cout << "NOT all patients can be seen!" << endl;
    return false;
}
