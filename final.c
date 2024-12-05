#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>

void attendees(void); //can list attendee info, show what events the attendee is going to
void attendeeSchedule(void);
void guest(void);
void guestSchedule(void);
void vendor(void); //list vendor info and what booth they are in
void event(void); //lists event details and who attends event, who hosts it, and what room it is in
                    //list events of a particular type
void booth(void); //shows which booths are occupied/free
void room(void); //Events held in that room
void printStuff(char *);
void addAttendee(void);
void eventList(void);

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

int main() {
    
    // Initialize MySQL connection object
    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("mysql_init() failed\n");
        return 1;
    }

    // Establish connection
    if (mysql_real_connect(conn, "localhost", "root", "ubuntu", "Project", 0, NULL, 0) == NULL) {
        printf("mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }
    /*
    // Execute a simple SELECT query
    if (mysql_query(conn, "SELECT * FROM Boats") != 0) {
        printf("mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    // Retrieve and process the result set
    res = mysql_store_result(conn);
    if (res == NULL) {
        printf("mysql_store_result() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    // Print column headers (optional)
    unsigned int num_fields = mysql_num_fields(res);
    MYSQL_FIELD *fields = mysql_fetch_fields(res);
    for (unsigned int i = 0; i < num_fields; i++) {
        printf("%s\t", fields[i].name);
    }
    printf("\n");

    // Fetch and print each row
    while ((row = mysql_fetch_row(res)) != NULL) {
        for (unsigned int i = 0; i < num_fields; i++) {
            printf("%s\t", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);
    */
    int option;

    while(1) {
        printf("\n***************Welcome to the Convention Administrator's Control Panel***************\n");
        printf("Please select an option:\n");
        printf("0: Same day Attendee registration\n");
        printf("1: Search for an attendee by name\n");
        printf("2: Lookup an attendee's event schedule by attendee name\n");
        printf("3: Search for a guest by name\n");
        printf("4: Lookup a guest's event hosting schedule\n");
        printf("5: Search an exhibitor by name and what booth they occupy\n");
        printf("6: Lookup an event type, and display guest host and room\n");
        printf("7: Look up occupied or free booths\n");
        printf("8: Look up occupied or free rooms\n");
        printf("9: Show list of attendees for a specific event\n");
        printf("10: Quit Control Panel\n");
        printf("***************************************************************************************\n");
        printf("Choose Option: ");
        scanf("%d", &option);
        switch(option) {
            case 0:
                addAttendee();
                break;
            case 1:
                attendees();
                break;
            case 2:
                attendeeSchedule();
                break;
            case 3:
                guest();
                break;
            case 4:
                guestSchedule();
                break;
            case 5:
                vendor();
                break;
            case 6:
                event();
                break;
            case 7:
                booth();
                break;
            case 8:
                room();
                break;
            case 9:
                eventList();
                break;
            case 10:
                printf("Exiting...\n");
                mysql_close(conn);
                return 0;
            default:
                printf("Not a Valid Option\n");
                break;
        }
    }

    return 0;
}

void addAttendee(void) {
    char query[256];
    char name[128];
    char type[16];
    char status[16];
    int max_ticket_no;
    int typeOption;
    int statusOption;

    printf("Enter Attendee's full name: ");
    scanf(" %[^\n]", name);
    printf("What type of ticket are they registering for?\n"); 
    printf("0 - day or 1 - weekend\n");
    printf("Enter Option: ");
    scanf("%d", &typeOption);
    printf("What status does this attendee have?\n");
    printf("0 - general admission, 1 - volunteer, 2 - press\n");
    printf("Enter Option: ");
    scanf("%d", &statusOption);

    switch(typeOption) {
        case 0:
            strcpy(type, "day");
            break;
        case 1:
            strcpy(type, "weekend");
            break;
    }

    switch(statusOption) {
        case 0:
            strcpy(status, "general");
            break;
        case 1:
            strcpy(type, "volunteer");
            break;
        case 2:
            strcpy(type, "press");
            break;
    }

    // Execute query to find the highest ticket_no
    if (mysql_query(conn, "SELECT MAX(ticket_no) FROM Attendee")) {
        printf("Error executing query: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (res) {
        row = mysql_fetch_row(res);
        // If no rows, start from 0
        if(row[0] != NULL) {
            max_ticket_no = atoi(row[0]);
        } else {
            max_ticket_no = 0;
        }
        //sprintf(ticket_no, "%d", max_ticket_no + 1);       // Increment by 1
        mysql_free_result(res);
    } else {
        printf("Error fetching result: %s\n", mysql_error(conn));
        return;
    }

    // Insert the new attendee
    sprintf(query, "INSERT INTO Attendee VALUES ('%d','%s','%s','%s')", max_ticket_no+1, name, type, status);
    if (mysql_query(conn, query)) {
        printf("Insert failed: %s\n", mysql_error(conn));
    } else {
        printf("New Attendee %s added\n", name); 
        printf("Unique ticket number: %d\n", max_ticket_no+1);
        printf("Ticket type: %s\n", type);
        printf("Attendee Status: %s\n\n", status);
    }
}

void printStuff(char * buffer) {
    //printf("%s\n", buffer);
    // Execute a simple SELECT query
    if (mysql_query(conn, buffer) != 0) {
        printf("mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // Retrieve and process the result set
    res = mysql_store_result(conn);
    if (res == NULL) {
        printf("mysql_store_result() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // Print column headers (optional)
    unsigned int num_fields = mysql_num_fields(res);
    MYSQL_FIELD *fields = mysql_fetch_fields(res);
    for (unsigned int j = 0; j < num_fields; j++) {
        printf("-----------------------");
    }
    printf("-\n");

    for (unsigned int i = 0; i < num_fields; i++) {
        printf("| %20s ", fields[i].name);
    }
    printf("|\n");

    for (unsigned int j = 0; j < num_fields; j++) {
        printf("-----------------------");
    }
    printf("-\n");

    // Fetch and print each row
    while ((row = mysql_fetch_row(res)) != NULL) {
        for (unsigned int i = 0; i < num_fields; i++) {
            printf("| %20s ", row[i] ? row[i] : "NULL");
        }
        printf("| \n");
        for (unsigned int j = 0; j < num_fields; j++) {
            printf("-----------------------");
        }
        printf("-\n");
    }
}

void attendees(void) {
    char name[20];
    char buffer[256];
    char status[20];
    //0 - general, 1 - volunteer, 2 - press
    int statOption;

    printf("Enter Attendee's name: ");
    scanf(" %[^\n]", name);

    printf("Enter attendee's ticket type:\n");
    printf("0 - general admission\n1 - volunteer\n2 - press\n");
    scanf("%d", &statOption);

    switch(statOption) {
        case 0:
            strcpy(status, "general");
            break;
        case 1:
            strcpy(status, "volunteer");
            break;
        case 2:
            strcpy(status, "press");
            break;
    }

    sprintf(buffer,"SELECT * FROM Attendee A WHERE A.name = '%s' AND A.status = '%s'", name, status);

    printStuff(buffer);

    mysql_free_result(res);
    return;
}

void attendeeSchedule() {
    char name[20];
    char buffer[256];

    printf("Enter Attendee's name: ");
    scanf(" %[^\n]", name);

    sprintf(buffer,"SELECT Ev.event_id, Ev.event_type, Ev.datetime, Ev.attendance, Ev.room_no, Ev.hall_no FROM Attendee, Attends, Event AS Ev WHERE Attendee.name = '%s' AND Attendee.ticket_no = Attends.ticket_no AND Attends.event_id = Ev.event_id", name);

    printStuff(buffer);

    mysql_free_result(res);
    return;
}

void guest(void) {
    char name[20];
    char buffer[256];

    printf("Enter Guest's name: ");
    scanf(" %[^\n]", name);

    sprintf(buffer,"SELECT Ex.ex_id, Ex.name, Ex.start, Ex.end FROM Exhibitor AS Ex, Guest AS G WHERE Ex.name = '%s' AND Ex.ex_id = G.ex_id", name);

    printStuff(buffer);

    mysql_free_result(res);
    return;
}

void guestSchedule(void) {
    char name[20];
    char buffer[256];

    printf("Enter Guest's name: ");
    scanf(" %[^\n]", name);

    sprintf(buffer,"SELECT Ev.event_id, Ev.event_type, Ev.datetime, Ev.attendance, Ev.room_no, Ev.hall_no FROM Exhibitor AS Ex, Hosts AS H, Event AS Ev WHERE Ex.name = '%s' AND Ex.ex_id = H.ex_id AND H.event_id = Ev.event_id", name);

    printStuff(buffer);

    mysql_free_result(res);
    return;
}

void vendor(void) {
    char name[20];
    char buffer[512];

    printf("Enter Vendor's name: ");
    scanf(" %[^\n]", name);

    sprintf(buffer,"WITH t1 AS (SELECT Ex.ex_id, Ex.name, Ex.start, Ex.end, V.vend_type FROM Exhibitor AS Ex, Vendor AS V WHERE Ex.name = '%s' AND Ex.ex_id = V.ex_id), t2 AS (SELECT O.ex_id, O.booth_no, O.hall_no FROM Exhibitor AS Ex, Occupied AS O WHERE Ex.name = '%s' AND Ex.ex_id = O.ex_id) SELECT * FROM t1 LEFT JOIN t2 ON t1.ex_id = t2.ex_id UNION SELECT * FROM t1 RIGHT JOIN t2 ON t1.ex_id = t2.ex_id", name, name);

    printStuff(buffer);

    mysql_free_result(res);
    return;
}

void event(void) {
    char name[20];
    char buffer[512];

    printf("Choose from the following options: panel, meet & greet, fan meet up, screening\n");
    printf("Enter Event type: ");
    scanf(" %[^\n]", name);

    sprintf(buffer,"WITH t1 AS (SELECT Ev.event_id, Ex.name FROM Event AS Ev, Hosts AS H, Exhibitor AS Ex WHERE Ev.event_type = '%s' AND Ev.event_id = H.event_id AND H.ex_id = Ex.ex_id), t2 AS (SELECT Ev.event_id, Ev.datetime, Ev.attendance, Ev.room_no, Ev.hall_no FROM Event AS Ev WHERE Ev.event_type = '%s') SELECT * FROM t1 LEFT JOIN t2 ON t1.event_id = t2.event_id UNION SELECT * FROM t1 RIGHT JOIN t2 ON t1.event_id = t2.event_id", name, name);

    printStuff(buffer);

    mysql_free_result(res);
    return;
}

void booth(void) {
    int option;
    char buffer[256];
    printf("---------------Booth Options---------------\n");
    printf("0 - Show all occupied booths\n");
    printf("1 - Show all empty booths\n");
    printf("-------------------------------------------\n");
    printf("Choose Option: ");
    scanf("%d", &option);

    switch(option) {
        case 0:
            sprintf(buffer, "SELECT Booth.booth_no, Booth.hall_no FROM Booth INNER JOIN Occupied ON Booth.booth_no = Occupied.booth_no AND Booth.hall_no = Occupied.hall_no");
            break;
        case 1:
            sprintf(buffer, "SELECT * FROM Booth WHERE NOT EXISTS (SELECT * FROM Occupied WHERE Booth.booth_no = Occupied.booth_no AND Booth.hall_no = Occupied.hall_no)");
            break;
        default:
            printf("Invalid Option, returning to main menu...\n");
            return;
    }

    printStuff(buffer);
    mysql_free_result(res);
    return;
}

void room(void) {
    int option;
    char buffer[256];
    printf("---------------Room Options---------------\n");
    printf("0 - Show all occupied rooms\n");
    printf("1 - Show all empty rooms\n");
    printf("------------------------------------------\n");
    printf("Choose Option: ");
    scanf("%d", &option);

    switch(option) {
        case 0:
            sprintf(buffer, "SELECT Room.room_no, Room.hall_no FROM Room INNER JOIN Event ON Room.room_no = Event.room_no AND Room.hall_no = Event.hall_no");
            break;
        case 1:
            sprintf(buffer, "SELECT * FROM Room WHERE NOT EXISTS (SELECT * FROM Event WHERE Room.room_no = Event.room_no AND Room.hall_no = Event.hall_no)");
            break;
        default:
            printf("Invalid Option, returning to main menu...\n");
            return;
    }

    printStuff(buffer);
    mysql_free_result(res);
    return;
}

void eventList(void) {
    char buffer[512];
    int eventId;

    printf("Enter Event ID to show list of attendees: ");
    scanf("%d", &eventId);

    sprintf(buffer,"SELECT A.ticket_no, A.name, A.ticket_type, A.status FROM Attendee AS A, Attends, Event AS E WHERE E.event_id = '%d' AND E.event_id = Attends.event_id AND Attends.ticket_no = A.ticket_no", eventId);

    printStuff(buffer);

    mysql_free_result(res);
    return;
}
