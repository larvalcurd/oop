namespace Bodies;

public abstract class CBody
{
    public abstract double GetDensity();
    public abstract double GetVolume();
    public abstract double GetMass();

    public double GetWeightInWater()
    {
        const double waterDensity = 1000.0; 
        return (GetDensity() - waterDensity) * GetVolume();
    }

    public override string ToString()
    {
        return $"Density = {GetDensity():F3}, Volume = {GetVolume():F3}, Mass = {GetMass():F3}";
    }
}