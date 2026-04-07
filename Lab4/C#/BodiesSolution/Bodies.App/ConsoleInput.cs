internal static class ConsoleInput
{
    public static int ReadPositiveInt()
    {
        while (true)
        {
            string? input = Console.ReadLine();

            if (int.TryParse(input, out int value) && value > 0)
            {
                return value;
            }

            Console.Write("Invalid value. Enter a positive integer: ");
        }
    }

    public static int ReadNonNegativeInt()
    {
        while (true)
        {
            string? input = Console.ReadLine();

            if (int.TryParse(input, out int value) && value >= 0)
            {
                return value;
            }

            Console.Write("Invalid value. Enter a non-negative integer: ");
        }
    }

    public static double ReadPositiveDouble()
    {
        while (true)
        {
            string? input = Console.ReadLine();

            if (double.TryParse(input, out double value) && value > 0)
            {
                return value;
            }

            Console.Write("Invalid value. Enter a positive number: ");
        }
    }
}