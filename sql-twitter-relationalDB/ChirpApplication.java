import java.sql.*;
import java.util.*;

/**
 * The class implements methods of the ChirpBase database interface.
 *
 * All methods of the class receive a Connection object through which all
 * communication to the database should be performed. Note: the
 * Connection object should not be closed by any method.
 *
 * Also, no method should throw any exceptions. In particular, in case
 * an error occurs in the database, then the method should print an
 * error message and call System.exit(-1);
 */

public class ChirpApplication {

    private Connection connection;

    /*
     * Constructor
     */
    public ChirpApplication(Connection connection) {
        this.connection = connection;
    }

    public Connection getConnection()
    {
        return connection;
    }

    /**
     * Takes as argument a string called theAddress.
     * Returns the userID for each tuple in ChirpUsers
     * whose address attribute value is theAddress.
     */

    public List<Integer> getUsersByAddress(String theAddress)
    {
        List<Integer> result = new ArrayList<Integer>();
        // your code here
        // Query to get users by address
        String addressQuery = "SELECT userID FROM chirpUsers Where address = '"+theAddress+"'";
        // Exception handling to catch SQL exceptions
        try {
            // Create a statement
            Statement addressStatement = connection.createStatement();
            // Execute query to get users by address
            ResultSet userIDs = addressStatement.executeQuery(addressQuery);
            // loop to get all returned values
            while(userIDs.next()){
                // Added to result list
                result.add(userIDs.getInt(1));
            }
            // Closing Statement and ResultSet is a good practice
            addressStatement.close();
            userIDs.close();
        } catch(SQLException e) {
            e.printStackTrace();
        }
        // end of your code
        return result;
    }


    /**
     * The ChirpUsers table has a Boolean attribute called active.  We’ll say that a
     * user is active if the value of active is TRUE, and we’ll say that a user is inactive
     * if that attribute is FALSE.  There may be some active users who haven’t made any posts
     * after December 31, 2017.  Update the ChirpUsers rows for these users so that they
     * become inactive.  (Don’t update rows of users that were already inactive.)
     * makeUsersInactive should return the number of users who were made inactive by your update.
     */
    
    public int makeUsersInactive() {
        // your code here; return 0 appears for now to allow this skeleton to compile.
        // Counter to count users who were made inactive
        int count = 0;
        // Statement to update Chirpusers by making users with no activity after 12/31 inactive
        String updateStatement = "UPDATE chirpUsers " +
                                    "SET active = FALSE " +
                                    "WHERE active " +
                                    "AND userID NOT IN " +
                                        "( SELECT posterID " +
                                          "FROM chirpPosts " +
                                          "WHERE postDate > DATE '12/31/2016')";
        try {
            Statement inactiveStatement = connection.createStatement();
            // execute Update instead of query as this updates the table
            count = inactiveStatement.executeUpdate(updateStatement);
            // It is a good practice to close the statements
            inactiveStatement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return count;
        // end of your code
    }


    /**
     * The purgeBadUsers method has has one integer parameter, censorLimit.  It invokes a
     * stored function purgeBadFunction that you will need to implement and store in the
     * database according to the description that appears in Section 5.
     * purgeBadFunction should take have the same parameter, censorLimit.  It will take
     * actions to purge all information about certain users from the database.
     * Section 5 explains which users will be purged, and what purging means.
     *
     * purgeBadFunction returns an integer value, and the purgeBadUsers method should
     * return the same integer value.
     */

    public int purgeBadUsers(int censorLimit)
    {
        // There's nothing special about the name storedFunctionResult
        int storedFunctionResult = 0;
        // Query to call the function with CensorLimit as a parameter
        String badUserQuery = "SELECT purgeBadFunction(?)";
        // your code here
        try {
            PreparedStatement badUserStatement = connection.prepareStatement(badUserQuery);
            // Replace the ? in prepared statement with censorLimit
            badUserStatement.setInt(1, censorLimit);
            // Call the stored function
            ResultSet result = badUserStatement.executeQuery();
            // Get the results
            result.next();
            // As the stored function only returns 1 value, we just do this once
            storedFunctionResult = result.getInt(1);
            // Closing statements and resultsets is a good practice
            badUserStatement.close();
            result.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        // end of your code
        return storedFunctionResult;
    }
};
