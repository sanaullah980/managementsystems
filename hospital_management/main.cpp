#include <iostream>
#include <map>
#include <string>
#include <limits>

struct Patient {
    int id{};
    std::string name, condition, room;
    int age{};
    bool admitted{true};
};
struct Doctor { int id{}; std::string name, specialty; };
struct Appointment { int patientId{}, doctorId{}; std::string time; };

class Hospital {
    std::map<int, Patient> patients;
    std::map<int, Doctor> doctors;
    std::map<int, Appointment> appointments;
public:
    bool addPatient(const Patient& p) {
        return p.id > 0 && patients.emplace(p.id, p).second;
    }
    bool addDoctor(const Doctor& d) {
        return d.id > 0 && doctors.emplace(d.id, d).second;
    }
    bool book(int appointmentId, int patientId, int doctorId, const std::string& time) {
        if (!patients.count(patientId) || !doctors.count(doctorId) || appointmentId <= 0) return false;
        return appointments.emplace(appointmentId, Appointment{patientId, doctorId, time}).second;
    }
    bool discharge(int id) {
        auto it = patients.find(id);
        if (it == patients.end() || !it->second.admitted) return false;
        it->second.admitted = false;
        return true;
    }
    void listPatients() const {
        if (patients.empty()) std::cout << "No patients registered.\n";
        for (const auto& [id, p] : patients)
            std::cout << id << " | " << p.name << " | age " << p.age << " | " << p.condition
                      << " | room " << p.room << " | " << (p.admitted ? "Admitted" : "Discharged") << '\n';
    }
    void listDoctors() const {
        if (doctors.empty()) std::cout << "No doctors registered.\n";
        for (const auto& [id, d] : doctors)
            std::cout << id << " | Dr. " << d.name << " | " << d.specialty << '\n';
    }
    void dashboard() const {
        int admitted = 0;
        for (const auto& [id, p] : patients) admitted += p.admitted;
        std::cout << "Patients: " << patients.size() << ", admitted: " << admitted
                  << ", doctors: " << doctors.size() << ", appointments: " << appointments.size() << '\n';
    }
};

int main() {
    Hospital hospital;
    int choice = 0;
    while (true) {
        std::cout << "\nHospital Management\n1 Add patient\n2 Add doctor\n3 Book appointment\n4 Discharge patient\n5 List patients\n6 List doctors\n7 Dashboard\n0 Exit\nChoice: ";
        if (!(std::cin >> choice)) return 0;
        if (choice == 0) break;
        if (choice == 1) {
            Patient p; std::cout << "ID age name condition room: ";
            std::cin >> p.id >> p.age >> p.name >> p.condition >> p.room;
            std::cout << (hospital.addPatient(p) ? "Patient added.\n" : "Invalid/duplicate ID.\n");
        } else if (choice == 2) {
            Doctor d; std::cout << "ID name specialty: "; std::cin >> d.id >> d.name >> d.specialty;
            std::cout << (hospital.addDoctor(d) ? "Doctor added.\n" : "Invalid/duplicate ID.\n");
        } else if (choice == 3) {
            int a, p, d; std::string time; std::cout << "Appointment ID patient ID doctor ID time(no spaces): ";
            std::cin >> a >> p >> d >> time;
            std::cout << (hospital.book(a, p, d, time) ? "Appointment booked.\n" : "Could not book appointment.\n");
        } else if (choice == 4) {
            int id; std::cout << "Patient ID: "; std::cin >> id;
            std::cout << (hospital.discharge(id) ? "Patient discharged.\n" : "Patient not found/already discharged.\n");
        } else if (choice == 5) hospital.listPatients();
        else if (choice == 6) hospital.listDoctors();
        else if (choice == 7) hospital.dashboard();
        else std::cout << "Unknown option.\n";
    }
}
