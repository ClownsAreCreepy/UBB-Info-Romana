using Sem12.Model;
using Sem12.Model.Validator;

namespace Sem12.Repository;

public class SarciniInFileRepo : InFileRepository<string, Sarcina>
{
    public SarciniInFileRepo(IValidator<Sarcina> validator, 
        string fileName) : 
        base(validator, fileName, SarciniParser.CreateEntity, SarciniParser.SaveEntity)
    {
    }
}

public class SarciniParser
{
    public static Sarcina CreateEntity(string line)
    {
        var tokens = line.Split(",");
        return new Sarcina
        {
            ID = tokens[0],
            TipDificultate = Enum.Parse<Dificultate>(tokens[1]),
            NrOreEstimate = int.Parse(tokens[2])
        };
    }
    
    public static string SaveEntity(Sarcina entity)
    {
        return string.Join(",", entity.ID, entity.TipDificultate, entity.NrOreEstimate);
    }
}