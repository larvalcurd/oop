using Bodies;

internal static class BodyPrinter
{
    public static void PrintAllBodies(IReadOnlyList<CBody> bodies)
    {
        Console.WriteLine("\n=== All bodies ===");

        if (bodies.Count == 0)
        {
            Console.WriteLine("No bodies found.");
            return;
        }

        for (int i = 0; i < bodies.Count; i++)
        {
            Console.WriteLine($"\nBody #{i + 1}:");
            PrintBody(bodies[i], 1);
        }
    }

    public static void PrintMaxMassBody(CBody? body)
    {
        Console.WriteLine("\n=== Body with max mass ===");

        if (body is null)
        {
            Console.WriteLine("No bodies found.");
            return;
        }

        PrintBody(body, 1);
    }

    public static void PrintMinWeightInWaterBody(CBody? body)
    {
        Console.WriteLine("\n=== Body with minimum weight in water ===");

        if (body is null)
        {
            Console.WriteLine("No bodies found.");
            return;
        }

        PrintBody(body, 1);
    }

    private static void PrintBody(CBody body, int indentLevel)
    {
        string indent = new string(' ', indentLevel * 2);
        Console.WriteLine($"{indent}{body}");

        if (body is CCompound compound)
        {
            var children = compound.GetChildren();

            for (int i = 0; i < children.Count; i++)
            {
                Console.WriteLine($"{indent}Child #{i + 1}:");
                PrintBody(children[i], indentLevel + 1);
            }
        }
    }
}