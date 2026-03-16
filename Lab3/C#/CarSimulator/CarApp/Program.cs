using CarApp;
using CarApp.Commands;

var car = new Car.Car();
var handler = new CommandHandler();

while (Console.ReadLine() is { } line)
{
    handler.HandleCommand(car, line);
}