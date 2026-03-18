namespace CalculatorApp.Commands;

public class PrintVarsCommand : ICommand
{
    public string Name => "printvars";

    public void Execute(Calculator.Calculator calc, string arguments)
    {
        foreach (var variable in calc.GetAllVariables())
        {
            string valueStr = double.IsNaN(variable.Value) 
                ? "nan" 
                : variable.Value.ToString("F2");
            
            Console.WriteLine($"{variable.Name}:{valueStr}");
        }
    }
}