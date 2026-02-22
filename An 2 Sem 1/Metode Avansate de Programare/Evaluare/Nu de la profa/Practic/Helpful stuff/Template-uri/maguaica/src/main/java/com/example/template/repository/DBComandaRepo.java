package com.example.template.repository;

import com.example.taximetrie.domeniu.Comanda;
import com.example.taximetrie.domeniu.Persoana;
import com.example.taximetrie.domeniu.Sofer;
import com.example.taximetrie.paging.Page;
import com.example.taximetrie.paging.Pageable;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class DBComandaRepo implements PagingComenzi<Long,Comanda> {
    private static final String URL = "jdbc:postgresql://127.0.0.1:5432/taximetrie";
    private static final String USER = "postgres";
    private static final String PASSWORD="1205";
    //private Validator<Comanda> validator;
    private Repository<Long,Persoana>repoPersoana;
    private Repository<Long, Sofer>repoSofer;
    public DBComandaRepo(Repository<Long, Persoana>repoPersoana, Repository<Long, Sofer>repoSofer) {
        this.repoPersoana = repoPersoana;
        this.repoSofer = repoSofer;
    }
    @Override
    public Optional<Comanda> findOne(Long id) {
        if(id==null)throw new IllegalArgumentException("Id-ul utilizatorului nu poate fi nul");

        String query = "SELECT * FROM comanda WHERE id = ?";
        Comanda comanda= null;
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query);) {

            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Long id_persoana= resultSet.getLong("id_persoana");
                Long id_sofer = resultSet.getLong("id_sofer");
                LocalDateTime data= resultSet.getTimestamp("data").toLocalDateTime();
                Optional<Persoana> persoana=repoPersoana.findOne(id_persoana);
                Optional<Sofer>sofer=repoSofer.findOne(id_sofer);
                comanda=new Comanda(persoana.orElse(null),sofer.orElse(null),data);
                comanda.setId(id);
            }

        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.ofNullable(comanda);
    }

    @Override
    public Iterable<Comanda> findAll() {
        Map<Long, Comanda> users = new HashMap<>();
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement("select * from comanda");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                Long id_persoana= resultSet.getLong("id_persoana");
                Long id_sofer= resultSet.getLong("id_sofer");
                LocalDateTime data= resultSet.getTimestamp("data").toLocalDateTime();
                Optional<Persoana> persoana=repoPersoana.findOne(id_persoana);
                Optional<Sofer>sofer=repoSofer.findOne(id_sofer);
                Comanda comanda=new Comanda(persoana.orElse(null),sofer.orElse(null),data);
                comanda.setId(id);

                users.put(comanda.getId(), comanda);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return users.values();
    }

    @Override
    public Optional<Comanda> save(Comanda entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Persoana nu poate fi nula");
        }
        String query = "INSERT INTO comanda(id_persoana,id_sofer,data) VALUES (?, ?, ?)";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query)) {

            //statement.setLong(1, entity.getId());
            statement.setLong(1, entity.getPersoana().getId());
            statement.setLong(2, entity.getTaximetrist().getId());
            statement.setTimestamp(3, Timestamp.valueOf(entity.getData()));

            int rowsAffected = statement.executeUpdate();
            if (rowsAffected > 0) {
                return Optional.of(entity);
            }
        } catch (SQLException e) {
            System.err.println("Error saving user: " + e.getMessage());
        }
        return Optional.empty();
    }

    @Override
    public Optional<Comanda> delete(Long aLong) {
        return Optional.empty();
    }


    @Override
    public Page<Long> getPagedPersoaneForSoferID(Long id, Pageable pageable) {
        ArrayList<Long> Ids= new ArrayList<>();
        String queryTotalNumberOfElements = "SELECT COUNT(DISTINCT id_persoana) AS count FROM comanda WHERE id_sofer = ?";
        String query = "SELECT DISTINCT id_persoana FROM comanda WHERE id_sofer = ? LIMIT ? OFFSET ?";
        int count=0;
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(query);
             PreparedStatement preparedStatementCount = connection.prepareStatement(queryTotalNumberOfElements)) {
            preparedStatement.setLong(1, id);
            int offset = (pageable.getPageNumber() - 1) * pageable.getPageSize();
            preparedStatement.setInt(2,pageable.getPageSize());
            preparedStatement.setInt(3,offset);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    long persoanaId = resultSet.getLong("id_persoana");
                    Ids.add(persoanaId);
                }
            }
            preparedStatementCount.setLong(1,id);

            try(ResultSet resultSet = preparedStatementCount.executeQuery()){
                while(resultSet.next()) {
                    count = resultSet.getInt("count");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return new Page<>(count, Ids);
    }


    /* COMENZI CU ID GENERAT !!! COMENZI RESTAUNRANTE
     public Optional<Order> save(Order entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Persoana nu poate fi nula");
        }
        String query = "INSERT INTO comanda(masa, date, status) VALUES (?, ?, ?)";
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS)) {
            statement.setLong(1, entity.getTableId());
            statement.setTimestamp(2, Timestamp.valueOf(entity.getDate()));
            statement.setString(3, entity.getStatus().toString());

            int rowsAffected = statement.executeUpdate();
            if (rowsAffected > 0) {
                try (ResultSet generatedKeys = statement.getGeneratedKeys()) {
                    if (generatedKeys.next()) {
                        long generatedId = generatedKeys.getLong(1);
                        entity.setId(generatedId);

                        for (Long itemId : entity.getMenuItems()) {
                            String query2 = "INSERT INTO comanda_item(id_comanda, id_item) VALUES (?, ?)";
                            try (PreparedStatement statement2 = connection.prepareStatement(query2)) {
                                statement2.setLong(1, generatedId);
                                statement2.setLong(2, itemId);

                                statement2.executeUpdate();
                            }
                        }
                        return Optional.of(entity);
                    }
                }
            }
        } catch (SQLException e) {
            System.err.println("Error saving order: " + e.getMessage());
        }
        return Optional.empty();
    }



     */
}
