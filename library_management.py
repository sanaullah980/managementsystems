# Library Management System

from __future__ import annotations
from dataclasses import dataclass, field
from datetime import datetime, timedelta
from typing import Dict, List, Optional


@dataclass
class Book:
    book_id: str
    title: str
    author: str
    category: str
    quantity: int = 1
    available: int = 1

    def __str__(self) -> str:
        return (
            f"Book ID: {self.book_id} | Title: {self.title} | Author: {self.author} | "
            f"Category: {self.category} | Available: {self.available}/{self.quantity}"
        )


@dataclass
class Member:
    member_id: str
    name: str
    email: str
    borrowed_books: List[str] = field(default_factory=list)

    def __str__(self) -> str:
        return f"Member ID: {self.member_id} | Name: {self.name} | Email: {self.email}"


class LibraryManagementSystem:
    def __init__(self) -> None:
        self.books: Dict[str, Book] = {}
        self.members: Dict[str, Member] = {}
        self.issued_books: Dict[str, Dict[str, str]] = {}

    def add_book(
        self,
        book_id: str,
        title: str,
        author: str,
        category: str,
        quantity: int = 1,
    ) -> Book:
        if book_id in self.books:
            raise ValueError("Book already exists.")
        book = Book(
            book_id=book_id,
            title=title,
            author=author,
            category=category,
            quantity=quantity,
            available=quantity,
        )
        self.books[book_id] = book
        return book

    def register_member(self, member_id: str, name: str, email: str) -> Member:
        if member_id in self.members:
            raise ValueError("Member already exists.")
        member = Member(member_id=member_id, name=name, email=email)
        self.members[member_id] = member
        return member

    def issue_book(self, member_id: str, book_id: str) -> str:
        member = self.members.get(member_id)
        book = self.books.get(book_id)
        if not member:
            raise ValueError("Member not found.")
        if not book:
            raise ValueError("Book not found.")
        if book.available <= 0:
            raise ValueError("No copies available.")
        if book_id in member.borrowed_books:
            raise ValueError("Book already borrowed by this member.")

        due_date = (datetime.now() + timedelta(days=14)).strftime("%Y-%m-%d")
        book.available -= 1
        member.borrowed_books.append(book_id)
        self.issued_books[book_id] = {
            "member_id": member_id,
            "due_date": due_date,
        }
        return due_date

    def return_book(self, member_id: str, book_id: str) -> None:
        member = self.members.get(member_id)
        book = self.books.get(book_id)
        if not member:
            raise ValueError("Member not found.")
        if not book:
            raise ValueError("Book not found.")
        if book_id not in member.borrowed_books:
            raise ValueError("This member did not borrow that book.")

        member.borrowed_books.remove(book_id)
        book.available += 1
        self.issued_books.pop(book_id, None)

    def search_book(self, keyword: str) -> List[Book]:
        lowered = keyword.lower()
        return [
            book
            for book in self.books.values()
            if lowered in book.title.lower() or lowered in book.author.lower() or lowered in book.category.lower()
        ]

    def list_books(self) -> List[Book]:
        return list(self.books.values())

    def list_members(self) -> List[Member]:
        return list(self.members.values())

    def get_issued_books(self) -> Dict[str, Dict[str, str]]:
        return self.issued_books


if __name__ == "__main__":
    library = LibraryManagementSystem()
    library.add_book("B001", "Clean Code", "Robert Martin", "Programming", 3)
    library.add_book("B002", "The Pragmatic Programmer", "Andrew Hunt", "Programming", 2)
    library.register_member("M001", "Sam Shah", "sam@example.com")
    library.register_member("M002", "Mila Ali", "mila@example.com")
    print(library.issue_book("M001", "B001"))
    print(library.search_book("Clean"))
    print(library.get_issued_books())
