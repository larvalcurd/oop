namespace CalculatorApp.Commands;

public interface ICommand
{
    string Name { get; }
    void Execute(Calculator.Calculator calc, string arguments);
}