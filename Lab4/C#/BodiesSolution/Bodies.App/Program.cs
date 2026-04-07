using Bodies;

internal class Program
{
    private static void Main()
    {
        var bodies = new List<CBody>();

        Console.Write("Enter number of top-level bodies: ");
        int bodyCount = ConsoleInput.ReadPositiveInt();

        for (int i = 0; i < bodyCount; i++)
        {
            Console.WriteLine($"\nEntering body #{i + 1}:");
            CBody body = BodyReader.ReadBody();
            bodies.Add(body);
        }

        BodyPrinter.PrintAllBodies(bodies);

        var maxMassBody = BodyUtils.FindBodyWithMaxMass(bodies);
        var minWeightInWaterBody = BodyUtils.FindBodyWithMinWeightInWater(bodies);

        BodyPrinter.PrintMaxMassBody(maxMassBody);
        BodyPrinter.PrintMinWeightInWaterBody(minWeightInWaterBody);
    }
}