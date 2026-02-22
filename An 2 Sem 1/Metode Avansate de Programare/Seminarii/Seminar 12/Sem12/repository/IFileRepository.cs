using Sem12.Model;
using Sem12.Model.Validator;

namespace Sem12.Repository;

public delegate T CreateEntityDelegate<T>(string line);
public delegate string SaveEntityDelegate<T>(T entity);

public abstract class InFileRepository <TId, T> : InMemoryRepository<TId, T> where T : Entity<TId>
{
    private bool fileLock;
    protected string fileName;
    protected CreateEntityDelegate<T> CreateEntity;
    protected SaveEntityDelegate<T> SaveEntity;
    
    protected InFileRepository(IValidator<T> validator,
        string fileName,
        CreateEntityDelegate<T> createEntity = null,
        SaveEntityDelegate<T> saveEntity = null) : base(validator)
    {
        this.fileName = fileName;
        Initialize(createEntity);
        this.SaveEntity = saveEntity;
    }

    protected void Initialize(CreateEntityDelegate<T> createEntity)
    {
        if (createEntity == null)
            return;

        this.CreateEntity = createEntity;
        LoadFromFile();
    }

    private void LoadFromFile()
    {
        fileLock = true;
        using StreamReader sr = new StreamReader(fileName);
        string line;
        while ((line = sr.ReadLine()) != null)
        {
            var entity = CreateEntity(line);
            Save(entity);
        }

        fileLock = false;
    }

    private void WriteToFile()
    {
        if (fileLock)
        {
            return;
        }
        using StreamWriter sw = new StreamWriter(fileName);
        foreach (var entity in FindAll())
        {
            sw.WriteLine(SaveEntity?.ToString());
        }
    }

    public override T? Save(T entity)
    {
        var saved = base.Save(entity);
        WriteToFile();
        return saved;
    }

    public override T? Delete(TId id)
    {
        return base.Delete(id);
    }

    public override T? Update(T entity)
    {
        return base.Update(entity);
    }
}