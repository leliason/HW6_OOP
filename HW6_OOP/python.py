import datetime
import math
from abc import ABC, abstractmethod

class Shape(ABC):
    @abstractmethod
    def shape_type(self) -> str:
        pass

    @abstractmethod
    def calculate_area(self) -> float:
        pass

class Circle(Shape):
    def __init__(self, radius: float):
        if radius < 0:
            raise ValueError("Radius cannot be negative.")
        self._radius = radius

    def shape_type(self) -> str:
        return "circle"

    def calculate_area(self) -> float:
        return math.pi * self._radius ** 2

class Square(Shape):
    def __init__(self, side: float):
        if side < 0:
            raise ValueError("Side cannot be negative.")
        self._side = side

    def shape_type(self) -> str:
        return "square"

    def calculate_area(self) -> float:
        return self._side ** 2

class ShapeLogger(ABC):
    @abstractmethod
    def log(self, message: str):
        pass

class ConsoleLogger(ShapeLogger):
    def log(self, message: str):
        print(message)

class FileLogger(ShapeLogger):
    def __init__(self, filepath: str):
        self._filepath = filepath

    def log(self, message: str):
        with open(self._filepath, "a") as f:
            f.write(message + "\n")

shape_history = []

def manage_shapes(shapes_data, logger: ShapeLogger = ConsoleLogger()):
    for shape in shapes_data:
        area      = shape.calculate_area()
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M")
        output    = f"[{timestamp}] Result for {shape.shape_type()}: {area}"

        logger.log(output)
        shape_history.append(output)

manage_shapes([
    Circle(5),
    Square(4),
], logger=ConsoleLogger())  # swap for FileLogger("log.txt") anytime