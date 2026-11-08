# Password Analyzer System

from __future__ import annotations
import math
import re
from dataclasses import dataclass, asdict
from typing import Dict


@dataclass
class PasswordReport:
    password: str
    length: int
    has_uppercase: bool
    has_lowercase: bool
    has_number: bool
    has_symbol: bool
    common_pattern: bool
    entropy: float
    score: int
    strength: str
    suggestions: list[str]


class PasswordAnalyzer:
    COMMON_PATTERNS = [
        "password",
        "admin",
        "welcome",
        "qwerty",
        "123456",
        "letmein",
        "abc123",
        "iloveyou",
    ]

    @staticmethod
    def calculate_entropy(password: str) -> float:
        if not password:
            return 0.0
        unique_chars = len(set(password))
        return round(len(password) * math.log2(max(unique_chars, 2)), 2)

    @staticmethod
    def has_common_pattern(password: str) -> bool:
        lowered = password.lower()
        return any(pattern in lowered for pattern in PasswordAnalyzer.COMMON_PATTERNS)

    @staticmethod
    def evaluate(password: str) -> PasswordReport:
        checks = {
            "has_uppercase": bool(re.search(r"[A-Z]", password)),
            "has_lowercase": bool(re.search(r"[a-z]", password)),
            "has_number": bool(re.search(r"\d", password)),
            "has_symbol": bool(re.search(r"[^A-Za-z0-9]", password)),
        }

        score = 0
        suggestions = []

        if len(password) >= 12:
            score += 25
        elif len(password) >= 8:
            score += 15
        else:
            suggestions.append("Use at least 8 characters.")

        for key, is_present in checks.items():
            if is_present:
                score += 15
            else:
                if key == "has_uppercase":
                    suggestions.append("Add uppercase letters.")
                elif key == "has_lowercase":
                    suggestions.append("Add lowercase letters.")
                elif key == "has_number":
                    suggestions.append("Add numbers.")
                elif key == "has_symbol":
                    suggestions.append("Add symbols (e.g. !@#$).")

        entropy = PasswordAnalyzer.calculate_entropy(password)
        score += min(20, int(entropy / 3))

        if PasswordAnalyzer.has_common_pattern(password):
            suggestions.append("Avoid common words and sequences.")
        else:
            score += 10

        if score >= 85:
            strength = "Very Strong"
        elif score >= 70:
            strength = "Strong"
        elif score >= 50:
            strength = "Medium"
        elif score >= 30:
            strength = "Weak"
        else:
            strength = "Very Weak"

        report = PasswordReport(
            password=password,
            length=len(password),
            has_uppercase=checks["has_uppercase"],
            has_lowercase=checks["has_lowercase"],
            has_number=checks["has_number"],
            has_symbol=checks["has_symbol"],
            common_pattern=PasswordAnalyzer.has_common_pattern(password),
            entropy=entropy,
            score=min(score, 100),
            strength=strength,
            suggestions=suggestions,
        )
        return report

    @staticmethod
    def summarize(passwords: list[str]) -> Dict[str, object]:
        results = [PasswordAnalyzer.evaluate(p) for p in passwords]
        summary = {
            "total": len(results),
            "average_score": round(sum(r.score for r in results) / len(results), 2) if results else 0,
            "strong_passwords": sum(1 for r in results if r.score >= 70),
            "weak_passwords": sum(1 for r in results if r.score < 50),
        }
        return summary


if __name__ == "__main__":
    samples = ["Password123!", "admin123", "A1b2!C3d4@", "StrongPass#2026"]
    for sample in samples:
        report = PasswordAnalyzer.evaluate(sample)
        print(report)
    print(PasswordAnalyzer.summarize(samples))
