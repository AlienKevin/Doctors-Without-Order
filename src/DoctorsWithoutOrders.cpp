#include "DoctorsWithoutOrders.h"
#include "map.h"
#include <climits>
#include <iostream>
#include <chrono>
using namespace std;

/* * * * Doctors Without Orders * * * */
bool canAllPatientsBeSeen(Vector<Doctor> &doctors,
                          Vector<Patient> &patients,
                          Map<string, Set<string>>& schedule);
bool canAllPatientsBeSeenHelper(Vector<Doctor> &doctors,
                                const Vector<Patient> &patients,
                                Set<int> &handledPatients,
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
    // Use auto keyword to avoid typing long
    // type definitions to get the timepoint
    // at this instant use function now()
    auto start = chrono::high_resolution_clock::now();

    Set<int> handledPatients;
    bool result = canAllPatientsBeSeenHelper(doctors, patients, handledPatients, schedule);

    // After function call
    auto stop = chrono::high_resolution_clock::now();
    // Subtract stop and start timepoints and
    // cast it to required unit. Predefined units
    // are nanoseconds, microseconds, milliseconds,
    // seconds, minutes, hours. Use duration_cast()
    // function.
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    // To get the value of duration use the count()
    // member function on the duration object
    cout << duration.count() << endl;

    return result;
}

bool canAllPatientsBeSeenHelper(Vector<Doctor> &doctors,
                                const Vector<Patient> &patients,
                                Set<int> &handledPatients,
                                Map<string, Set<string>>& schedule) {
    if (handledPatients.size() == patients.size()) {
        return true;
    }
    bool findMatch = false;
    for (int i = 0; i < patients.size(); i ++) {
        for (int j = 0; j < doctors.size(); j ++) {
            if (!handledPatients.contains(i) && doctors[j].hoursFree >= patients[i].hoursNeeded) {
                Patient patient = patients[i];
                // change
                doctors[j].hoursFree -= patients[i].hoursNeeded;
                handledPatients.add(i);
                // explore
                if (canAllPatientsBeSeenHelper(doctors, patients, handledPatients, schedule)) {
                    schedule[doctors[j].name].add(patient.name);
                    findMatch = true;
                }
                // un-change
                handledPatients.remove(i);
                doctors[j].hoursFree += patient.hoursNeeded;

                if (findMatch) {
                    return true;
                }
            }
        }
    }
    return false;
}
