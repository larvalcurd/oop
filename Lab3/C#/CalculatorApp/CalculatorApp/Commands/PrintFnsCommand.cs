namespace CalculatorApp.Commands;

public class PrintFnsCommand : ICommand
{
    public string Name => "printfns";

    public void Execute(Calculator.Calculator calc, string arguments)
    {
        foreach (var function in calc.GetAllFunctions())
        {
            double value = function.Evaluate(calc);
            
            string valueStr = double.IsNaN(value) 
                ? "nan" 
                : value.ToString("F2");
            
            Console.WriteLine($"{function.Name}:{valueStr}");
        }
    }
}