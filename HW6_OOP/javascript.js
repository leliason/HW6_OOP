class Shape {
    calculateArea() {
        throw new Error("calculateArea() must be implemented by subclass.");
    }
    get shapeName() {
        throw new Error("shapeName must be implemented by subclass.");
    }
}

class Circle extends Shape {
    constructor(radius) {
        super();
        if (radius < 0) throw new Error("Radius cannot be negative.");
        this._radius = radius;
    }
    get shapeName() { return "circle"; }
    calculateArea() { return Math.PI * this._radius * this._radius; }
}

class Rect extends Shape {
    constructor(w, h) {
        super();
        if (w < 0) throw new Error("Width cannot be negative.");
        if (h < 0) throw new Error("Height cannot be negative.");
        this._w = w;
        this._h = h;
    }
    get shapeName() { return "rect"; }
    calculateArea() { return this._w * this._h; }
}

class ConsoleLogger {
    log(message) { console.log("Audit Log:", message); }
}

class UILogger {
    constructor(elementId) {
        this._elementId = elementId;
    }
    log(message) {
        document.getElementById(this._elementId).innerText = message;
    }
}

const history = [];

function handleShapeRequest(shape, logger = new ConsoleLogger()) {
    const result    = shape.calculateArea();
    const statusMsg = `Processed ${shape.shapeName} with area ${result}`;

    logger.log(statusMsg);
    history.push({ item: shape.shapeName, val: result, time: Date.now() });
}

handleShapeRequest(new Circle(5), new ConsoleLogger());
handleShapeRequest(new Rect(4, 6), new UILogger("status-display"));