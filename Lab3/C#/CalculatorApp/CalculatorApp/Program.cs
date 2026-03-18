using CalculatorApp;

var handler = new CommandHandler();

while (Console.ReadLine() is { } line)
{
    handler.Handle(line);
}