using System;
using System.Collections.Generic;
using System.IO;

public abstract class Shape
{
    public abstract string ShapeType { get; }
    public abstract double CalculateArea();

    protected static void Validate(double value, string name)
    {
        if (value < 0) throw new ArgumentException($"{name} cannot be negative.", name);
    }
}

public class Circle : Shape
{
    private readonly double _radius;
    public Circle(double radius) { Validate(radius, nameof(radius)); _radius = radius; }
    public override string ShapeType => "Circle";
    public override double CalculateArea() => Math.PI * _radius * _radius;
}

public class Rectangle : Shape
{
    private readonly double _width, _height;
    public Rectangle(double width, double height) { Validate(width, nameof(width)); Validate(height, nameof(height)); _width = width; _height = height; }
    public override string ShapeType => "Rectangle";
    public override double CalculateArea() => _width * _height;
}

public class Triangle : Shape
{
    private readonly double _base, _height;
    public Triangle(double @base, double height) { Validate(@base, nameof(@base)); Validate(height, nameof(height)); _base = @base; _height = height; }
    public override string ShapeType => "Triangle";
    public override double CalculateArea() => 0.5 * _base * _height;
}

public interface IShapeLogger
{
    void Log(string message);
}

public class ConsoleLogger : IShapeLogger
{
    public void Log(string message) => Console.WriteLine("DEBUG: " + message);
}

public class FileLogger : IShapeLogger
{
    private readonly string _filePath;
    public FileLogger(string filePath) { _filePath = filePath; }
    public void Log(string message) => File.AppendAllText(_filePath, message + Environment.NewLine);
}

public class ShapeManager
{
    public static List<string> History = new List<string>();
    private readonly IShapeLogger _logger;

    public ShapeManager(IShapeLogger logger) { _logger = logger; }

    public void ProcessShape(Shape shape)
    {
        double area = shape.CalculateArea();
        string report = $"Shape: {shape.ShapeType}, Area: {area}, Date: {DateTime.Now}";
        _logger.Log(report);
        History.Add(report);
    }
}

IShapeLogger logger = new ConsoleLogger(); // swap for FileLogger anytime
var manager = new ShapeManager(logger);

manager.ProcessShape(new Circle(5));
manager.ProcessShape(new Rectangle(4, 6));
manager.ProcessShape(new Triangle(3, 8));