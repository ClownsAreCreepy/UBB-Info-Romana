using System.Globalization;
using Sem12.Model;
using Sem12.Model.Validator;

namespace Sem12.Repository;

public class PontajInFileRepo : InFileRepository<string, Pontaj> 
{
    public PontajInFileRepo(IValidator<Pontaj> validator, 
        string fileName, 
        IRepository<string, Angajat> angajatiRepo,
        IRepository<string, Sarcina> sarcinaRepo)
        : base(validator, fileName, null, PontajParser.SaveEntity)
    {
        var pontajParser = new PontajParser(angajatiRepo, sarcinaRepo);
        Initialize(pontajParser.CreateEntity);
    }
}

public class PontajParser(
    IRepository<string, Angajat> AngajatiRepo,
    IRepository<string, Sarcina> SarcinaRepo)
{
    public Pontaj CreateEntity(string line)
    {
        var tokens = line.Split(",");
        return new Pontaj
        {
            ID = tokens[0] + tokens[1],
            Angajat = AngajatiRepo.FindOne(tokens[0]),
            Sarcina = SarcinaRepo.FindOne(tokens[1]),
            Date = DateTime.ParseExact(tokens[2], "d/M/yyyy", CultureInfo.InvariantCulture)
        };
    }
    
    public static string SaveEntity(Pontaj entity)
    {
        return string.Join(",",
                entity.Angajat?.ID,
                entity.Sarcina?.ID,
                entity.Date.ToString("d/M/yyyy", CultureInfo.InvariantCulture));
    }
}