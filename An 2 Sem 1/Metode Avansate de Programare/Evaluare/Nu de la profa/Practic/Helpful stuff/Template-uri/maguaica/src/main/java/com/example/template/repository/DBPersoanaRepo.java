package com.example.template.repository;


import com.example.template.domeniu.Persoana;


import java.sql.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class DBPersoanaRepo {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/taximetrie";
    private static final String USER = "postgres";
    private static final String PASSWORD="1205";
    public DBPersoanaRepo() {

    }

    public Optional<Persoana> findOne(Long id) {
        if(id==null)throw new IllegalArgumentException("Id-ul utilizatorului nu poate fi nul");

        String query = "SELECT * FROM persoana WHERE id = ?";
        Persoana persoana= null;
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query);) {

            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                String nume= resultSet.getString("nume");
                String username = resultSet.getString("username");
                persoana = new Persoana(username,nume);
                persoana.setId(id);
            }

        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.ofNullable(persoana);
    }
    public Iterable<Persoana> findAll() {
        Map<Long, Persoana> users = new HashMap<>();
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement("select * from persoana");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String nume= resultSet.getString("nume");
                String username = resultSet.getString("username");
                Persoana persoana = new Persoana(username,nume);
                persoana.setId(id);

                users.put(persoana.getId(), persoana);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return users.values();
    }


    public Optional<Persoana> save(Persoana entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Persoana nu poate fi nula");
        }
        String query = "INSERT INTO users(username,nume) VALUES ( ?, ?)";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            //statement.setLong(1, entity.getId());
            statement.setString(1, entity.getUsername());
            statement.setString(2, entity.getNume());

            int rowsAffected = statement.executeUpdate();
            if (rowsAffected > 0) {
                return Optional.of(entity);
            }
        } catch (SQLException e) {
            System.err.println("Error saving user: " + e.getMessage());
        }
        return Optional.empty();
    }


    public Optional<Persoana> delete(Long aLong) {
        return Optional.empty();
    }


}
