#create validator
validator = StudentValidator()
#crate repository
rep = InMemoryRepository(None)
#create console provide(inject) a validator and a repository
srv = StudentService(rep, validator)
#create console provide service
ui = Console(srv)
ui.showUI()