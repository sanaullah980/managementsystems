# Hospital Management System

from __future__ import annotations
from dataclasses import dataclass, field
from typing import Dict, List, Optional


@dataclass
class Patient:
    patient_id: str
    name: str
    age: int
    disease: str
    room_no: str
    status: str = "Admitted"

    def __str__(self) -> str:
        return (
            f"Patient ID: {self.patient_id} | Name: {self.name} | Age: {self.age} | "
            f"Disease: {self.disease} | Room: {self.room_no} | Status: {self.status}"
        )


@dataclass
class Doctor:
    doctor_id: str
    name: str
    specialty: str
    schedule: List[str] = field(default_factory=list)

    def add_schedule(self, slot: str) -> None:
        self.schedule.append(slot)

    def __str__(self) -> str:
        return f"Dr. {self.name} ({self.specialty}) | ID: {self.doctor_id}"


class HospitalManagementSystem:
    def __init__(self) -> None:
        self.patients: Dict[str, Patient] = {}
        self.doctors: Dict[str, Doctor] = {}
        self.appointments: Dict[str, Dict[str, str]] = {}

    def add_doctor(self, doctor_id: str, name: str, specialty: str) -> Doctor:
        doctor = Doctor(doctor_id=doctor_id, name=name, specialty=specialty)
        self.doctors[doctor_id] = doctor
        return doctor

    def add_patient(
        self,
        patient_id: str,
        name: str,
        age: int,
        disease: str,
        room_no: str,
    ) -> Patient:
        patient = Patient(
            patient_id=patient_id,
            name=name,
            age=age,
            disease=disease,
            room_no=room_no,
        )
        self.patients[patient_id] = patient
        return patient

    def schedule_appointment(
        self,
        appointment_id: str,
        patient_id: str,
        doctor_id: str,
        date_time: str,
    ) -> None:
        if patient_id not in self.patients:
            raise ValueError("Patient not found.")
        if doctor_id not in self.doctors:
            raise ValueError("Doctor not found.")
        self.appointments[appointment_id] = {
            "patient_id": patient_id,
            "doctor_id": doctor_id,
            "date_time": date_time,
        }

    def discharge_patient(self, patient_id: str) -> None:
        if patient_id not in self.patients:
            raise ValueError("Patient not found.")
        patient = self.patients[patient_id]
        patient.status = "Discharged"

    def search_patient(self, patient_id: str) -> Optional[Patient]:
        return self.patients.get(patient_id)

    def list_patients(self) -> List[Patient]:
        return list(self.patients.values())

    def list_doctors(self) -> List[Doctor]:
        return list(self.doctors.values())

    def patient_count_by_status(self, status: str) -> int:
        return sum(1 for patient in self.patients.values() if patient.status == status)

    def dashboard(self) -> Dict[str, int]:
        return {
            "total_patients": len(self.patients),
            "total_doctors": len(self.doctors),
            "admitted_patients": self.patient_count_by_status("Admitted"),
            "discharged_patients": self.patient_count_by_status("Discharged"),
            "appointments": len(self.appointments),
        }


if __name__ == "__main__":
    hospital = HospitalManagementSystem()
    hospital.add_doctor("D001", "Alice Johnson", "Cardiology")
    hospital.add_doctor("D002", "Michael Smith", "Neurology")
    hospital.add_patient("P001", "John Doe", 42, "Heart disease", "ICU-12")
    hospital.add_patient("P002", "Jane Doe", 29, "Migraine", "Ward-B4")
    hospital.schedule_appointment("A001", "P001", "D001", "2026-11-08 10:30")
    hospital.schedule_appointment("A002", "P002", "D002", "2026-11-08 12:00")
    print("Hospital Dashboard:", hospital.dashboard())
    for patient in hospital.list_patients():
        print(patient)
    for doctor in hospital.list_doctors():
        print(doctor)
