//package curs3.io.repository;
//
//
//
//
//import curs3.io.domain.Entity;
//import curs3.io.domain.validators.Validator;
//
//import java.io.*;
//
//import java.util.Arrays;
//import java.util.List;
//
//
//
//public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID,E> {
//    String fileName;
//
//    public AbstractFileRepository(String fileName, Validator<E> validator) {
//        super(validator);
//
//
//    }
//
//    private void loadData() { //decorator pattern
//        try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
//            String newLine;
//            while ((newLine = reader.readLine()) != null) {
//                System.out.println(newLine);
//                List<String> data = Arrays.asList(newLine.split(";"));
//                E entity = extractEntity(data);
//                super.save(entity);
//            }
//
//        } catch (FileNotFoundException e) {
//            e.printStackTrace();
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//
//    }
//    public abstract E extractEntity(List<String> attributes);
//    protected abstract String createEntityAsString(E entity);
//
//
//
//    protected void writeToFile(E entity) {
//        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName, true))) {
//
//            writer.write(createEntityAsString(entity));
//            writer.newLine();
//
//        } catch (FileNotFoundException e) {
//            e.printStackTrace();
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//    }
//}
