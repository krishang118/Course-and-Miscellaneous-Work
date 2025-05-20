let firstValue = ''; 
let waitingForSecondValue = false; 
function appendValue(value) {
    let display = document.getElementById('display');
    if (display.value === 'Error') {
        display.value = '';
    }
    if (waitingForSecondValue) {
        display.value = value;
        waitingForSecondValue = false;
    } else {
        display.value += value;
    }
}
function clearDisplay() {
    document.getElementById('display').value = '';
    firstValue = '';
    waitingForSecondValue = false;
}  
function backspace() {
    let display = document.getElementById('display');
    display.value = display.value.slice(0, -1);
}
function calculate() {
    let display = document.getElementById('display');
    let expression = display.value;
    if (firstValue !== '') {
        expression = firstValue + expression;
    }
    expression = expression.replace(/sin\(([^)]+)\)/g, function(match, degree) {
        return Math.sin(parseFloat(degree) * Math.PI / 180);
    });
    expression = expression.replace(/cos\(([^)]+)\)/g, function(match, degree) {
        return Math.cos(parseFloat(degree) * Math.PI / 180);
    });
    expression = expression.replace(/tan\(([^)]+)\)/g, function(match, degree) {
        return Math.tan(parseFloat(degree) * Math.PI / 180);
    });
    expression = expression.replace(/ cm in inches is/g, '*0.393701');
    expression = expression.replace(/ inches in cm is/g, '*2.54');
    expression = expression.replace(/ meters in feet is/g, '*3.28084');
    expression = expression.replace(/ feet in meters is/g, '*0.3048');
    expression = expression.replace(/ yards in inches is/g, '*36');
    expression = expression.replace(/ inches in yards is/g, '*0.0277778');
    expression = expression.replace(/ kilometers in miles is/g, '*0.621371');
    expression = expression.replace(/ miles in kilometers is/g, '*1.60934');
    expression = expression.replace(/ ounces in grams is/g, '*28.3495');
    expression = expression.replace(/ grams in ounces is/g, '*0.035274');
    expression = expression.replace(/ pounds in kilograms is/g, '*0.453592');
    expression = expression.replace(/ kilograms in pounds is/g, '*2.20462');
    expression = expression.replace(/ liters in gallons is/g, '*0.264172');
    expression = expression.replace(/ gallons in liters is/g, '*3.78541');
    expression = expression.replace(/ years in days is/g, '*365');
    expression = expression.replace(/ days in years is/g, '*0.00273791');
    expression = expression.replace(/ °C in °F is/g, '*1.8+32');
    expression = expression.replace(/ °F in °C is/g, '-32/1.8');
    expression = expression.replace(/ °C in K is/g, '+273.15');
    expression = expression.replace(/ K in °C is/g, '-273.15');
    expression = expression.replace(/ kmph in mph is/g, '*0.621371');
    expression = expression.replace(/ mph in kmph is/g, '*1.60934');
    expression = expression.replace(/ degrees in radians is/g, '*Math.PI/180');
    expression = expression.replace(/ radians in degrees is/g, '*180/Math.PI');
    expression = expression.replace(/\^/g, '**');
    try {
        let result = eval(expression); 
        if (!isNaN(result)) {
            display.value = result;
            firstValue = result.toString(); 
            waitingForSecondValue = true; 
        } else {
            display.value = 'Error'; 
        }
    } catch (error) {
        display.value = 'Error'; 
    }
}
function factorial(x) {
    if (x === 0 || x === 1) {
        return 1;
    } else if (x < 0) {
        return 'Error: Factorial is not defined for negative numbers';
    } else {
        let result = 1;
        for (let i = 2; i <= x; i++) {
            result *= i;
        }
        return result;
    }
}
function squareRoot() {
    let display = document.getElementById('display');
    let expression = display.value.trim();
    try {
        let result = eval(expression); 
        if (!isNaN(result) && result >= 0) {
            let sqrtValue = Math.sqrt(result);
            display.value = sqrtValue; 
        } else {
            display.value = 'Error'; 
        }
    } catch (error) {
        display.value = 'Error'; 
    }
}
function calculateFactorial() {
    let display = document.getElementById('display');
    let value = parseFloat(display.value);
    if (!isNaN(value) && Number.isInteger(value) && value >= 0) {
        display.value = factorial(value);
    } else {
        display.value = 'Error';
    }
}
function ln(x) {
    return Math.log(x);
}
function log10(x) {
    return Math.log10(x);
}
function calculateNaturalLog() {
    let display = document.getElementById('display');
    let value = parseFloat(display.value);
    if (!isNaN(value) && value > 0) {
        display.value = ln(value);
    } else {
        display.value = 'Error';
    }
}
function calculateLog10() {
    let display = document.getElementById('display');
    let value = parseFloat(display.value);
    if (!isNaN(value) && value > 0) {
        display.value = log10(value);
    } else {
        display.value = 'Error';
    }
}
