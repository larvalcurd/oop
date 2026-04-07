namespace Bodies;

public static class BodyUtils
{
    public static CBody? FindBodyWithMaxMass(IEnumerable<CBody> bodies)
    {
        return bodies.OrderByDescending(body => body.GetMass()).FirstOrDefault();
    }

    public static CBody? FindBodyWithMinWeightInWater(IEnumerable<CBody> bodies)
    {
        return bodies.OrderBy(body => body.GetWeightInWater()).FirstOrDefault();
    }
}