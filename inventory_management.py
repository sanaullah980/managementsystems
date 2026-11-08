# Business Inventory Management System

from __future__ import annotations
from dataclasses import dataclass, field
from typing import Dict, List, Optional


@dataclass
class Product:
    sku: str
    name: str
    category: str
    price: float
    quantity: int
    reorder_level: int

    def __str__(self) -> str:
        return (
            f"SKU: {self.sku} | Name: {self.name} | Category: {self.category} | "
            f"Price: ${self.price:.2f} | Qty: {self.quantity}"
        )


class InventoryManagementSystem:
    def __init__(self) -> None:
        self.products: Dict[str, Product] = {}

    def add_product(
        self,
        sku: str,
        name: str,
        category: str,
        price: float,
        quantity: int,
        reorder_level: int = 10,
    ) -> Product:
        if sku in self.products:
            raise ValueError("SKU already exists.")
        product = Product(sku, name, category, price, quantity, reorder_level)
        self.products[sku] = product
        return product

    def get_product(self, sku: str) -> Optional[Product]:
        return self.products.get(sku)

    def sell_product(self, sku: str, quantity: int) -> float:
        product = self.products.get(sku)
        if not product:
            raise ValueError("Product not found.")
        if quantity > product.quantity:
            raise ValueError("Not enough inventory.")
        product.quantity -= quantity
        return product.price * quantity

    def restock_product(self, sku: str, quantity: int) -> None:
        product = self.products.get(sku)
        if not product:
            raise ValueError("Product not found.")
        product.quantity += quantity

    def apply_discount(self, sku: str, percentage: float) -> float:
        product = self.products.get(sku)
        if not product:
            raise ValueError("Product not found.")
        new_price = product.price * (1 - percentage / 100)
        product.price = round(new_price, 2)
        return product.price

    def low_stock_items(self) -> List[Product]:
        return [product for product in self.products.values() if product.quantity <= product.reorder_level]

    def inventory_value(self) -> float:
        return sum(product.price * product.quantity for product in self.products.values())

    def total_products(self) -> int:
        return len(self.products)

    def generate_report(self) -> Dict[str, float]:
        return {
            "total_products": float(self.total_products()),
            "inventory_value": self.inventory_value(),
            "low_stock_count": float(len(self.low_stock_items())),
        }


if __name__ == "__main__":
    inventory = InventoryManagementSystem()
    inventory.add_product("P100", "Laptop", "Electronics", 850.00, 12, 5)
    inventory.add_product("P200", "Notebook", "Stationery", 15.50, 48, 12)
    print(inventory.sell_product("P100", 3))
    print(inventory.low_stock_items())
    print(inventory.generate_report())
