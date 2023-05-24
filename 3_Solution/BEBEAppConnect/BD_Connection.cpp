#include "BD_Connection.h"
#include "Tutore.h"

BD_Connection* BD_Connection::instance = nullptr;

bool BD_Connection::createUser(string nr,string username, string parola, string nume, string prenume) {
    try {

        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
            INSERT INTO Tutori (username, parola, nume, prenume) VALUES (? , ? , ? , ? );
        )");

          
        const std::string u1 = username;
        const std::string u2 = parola;
        const std::string u3 = nume;
        const std::string u4 = prenume;

        stmt.bind(0, u1.c_str());
        stmt.bind(1, u2.c_str());
        stmt.bind(2, u3.c_str());
        stmt.bind(3, u4.c_str());

        nanodbc::result rez = stmt.execute();
        if (rez.affected_rows() == 0) {
            return false;
        }

        return rez.has_affected_rows();
    }
    catch (nanodbc::database_error err) {
        std::cout << err.what();
    }
}

bool BD_Connection::Get_LogIn(string nr, string username, string parola)
{
    try {
        //Construim interogarea SQL parametrizată
        nanodbc::statement stmt(conn);
      
        nanodbc::prepare(stmt, R"(
           SELECT username, parola 
           FROM Tutori 
           WHERE username= ? AND  parola= ?;
        )");
        
        //Setăm valorile parametrilor
        const std::string u1 = username;
        const std::string u2 = parola;
        stmt.bind(0, u1.c_str());
        stmt.bind(1, u2.c_str());

        // Executăm interogarea
        nanodbc::result rez = stmt.execute();

        if (rez.affected_rows() == 0) {
            return false;
        }

        while (rez.next()) {
            std::string user = rez.get<string>(0);
            std::string pass = rez.get<string>(1);
            if ((user == username) && (pass == parola)) {
                return true;
            }
        }



    }
    catch (nanodbc::database_error err) {
        cout<< err.what();
    }
}

int BD_Connection::GetIdUsername(string username)
{
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
           SELECT ID_Tutore FROM Tutori WHERE username = ?;
        )");
    const std::string u = username;
    stmt.bind(0, u.c_str());
    nanodbc::result rez = stmt.execute();
    
    rez.next();
    return rez.get<int>(0);
    if (rez.has_affected_rows() == 0) {
        return -1;
    }

   
}
int BD_Connection::getnamekid(string nume_copil)
{
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
           SELECT ID_Copil FROM Copii WHERE nume_copil = ?;
        )");
    const std::string u =nume_copil ;
    stmt.bind(0, u.c_str());
    nanodbc::result rez = stmt.execute();

    int a = rez.affected_rows();
    int b = rez.has_affected_rows();
    int c = rez.columns();
    if (rez.affected_rows() == 0) {
        return false;
    }
    rez.next();

    return rez.get<int>(0);
    

}
bool BD_Connection::creatKid(string nr, string nume, string prenume, string data_nastere, int varsta,string username)
{   try{
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
            INSERT INTO Copii (nume_copil, prenume_copil, varsta_copil, data_nastere_copil, ID_Tutore) VALUES ( ?, ?, ? , ? , ? );
        )");

    const std::string u1 = nume;
    const std::string u2 = prenume;
    const int u3 = varsta;
    const std::string u4 = data_nastere;
    const int u5 = GetIdUsername(username);

    stmt.bind(0, u1.c_str());
    stmt.bind(1, u2.c_str());
    stmt.bind(2, &u3);
    stmt.bind(3, u4.c_str());
    stmt.bind(4, &u5);

    nanodbc::result rez = stmt.execute();
    if (rez.affected_rows() == 0) {
        return false;
    }

    return rez.has_affected_rows();

}
catch (nanodbc::database_error err) {
    cout << err.what();
}
  

}
bool BD_Connection::addFood(string nr, string tip_hrana, int cantitate_hrana, string moment_hranire, string nume_copil)
{
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
            INSERT INTO Hraniri (tip_hrana, cantitate_hrana, moment_hranire, ID_Copil) VALUES ( ?, ?, ? , ? );
        )");

    const std::string u1 = tip_hrana;
    const int u2 = cantitate_hrana;
    const std::string u3 = moment_hranire;
    const int u4 = getnamekid(nume_copil);

    stmt.bind(0, u1.c_str());
    stmt.bind(1, &u2);
    stmt.bind(2, u3.c_str());
    stmt.bind(3, &u4);


    nanodbc::result rez = stmt.execute();
    if (rez.affected_rows() == 0) {
        return false;
    }

    return rez.has_affected_rows();

}
bool BD_Connection::addSleep(string nr, string interval_orar, string nume_copil)
{
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
            INSERT INTO Ore_Somn (interval_orar_somn, ID_Copil) VALUES ( ?, ? );
        )");

    const std::string u1 = interval_orar;
    const int u2 = getnamekid(nume_copil);

    stmt.bind(0, u1.c_str());
    stmt.bind(1, &u2);


    nanodbc::result rez = stmt.execute();
    if (rez.affected_rows() == 0) {
        return false;
    }
    return rez.has_affected_rows();
}
bool BD_Connection::addIllnesses(string nr, string nume_boala, string perioada_temperatura, string ora_consultatie_medic, string concluzie_medic, string analize, string rezultate_analize, string lista_vaccinuri, string nume_copil)
{
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
            INSERT INTO  Boli (nume_boala, periaoda_temperatura, ora_consultatie_medic, concluzie_medic, analize, rezultate_analize, lista_vaccinuri, ID_Copil) VALUES ( ?, ? , ? , ? , ? , ? , ? , ? );
        )");

    const std::string u1 = nume_boala;
    const std::string u2 = perioada_temperatura;
    const std::string u3 = ora_consultatie_medic;
    const std::string u4 = concluzie_medic;
    const std::string u5 = analize;
    const std::string u6 = rezultate_analize;
    const std::string u7 = lista_vaccinuri;
    const int u8 = getnamekid(nume_copil);

    stmt.bind(0, u1.c_str());
    stmt.bind(1, u2.c_str());
    stmt.bind(2, u3.c_str());
    stmt.bind(3, u4.c_str());
    stmt.bind(4, u5.c_str());
    stmt.bind(5, u6.c_str());
    stmt.bind(6, u7.c_str());
    stmt.bind(7, &u8);

    nanodbc::result rez = stmt.execute();
    if (rez.affected_rows() == 0) {
        return false;
    }
    return rez.has_affected_rows();
}
bool BD_Connection::addSize(string nr, int dimenziune_cap, int inaltime, int greutate, string nume_copil)
{
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
            INSERT INTO Monitorizari_Crestere (dimensiune_cap, inaltime, greutate, ID_Copil) VALUES ( ?, ? , ? , ?);
        )");

    const int u1 = dimenziune_cap;
    const int u2 = inaltime;
    const int u3 = greutate;
    const int u4 = getnamekid(nume_copil);

    stmt.bind(0, &u1);
    stmt.bind(1, &u2);
    stmt.bind(2, &u3);
    stmt.bind(3, &u4);

    nanodbc::result rez = stmt.execute();
    if (rez.affected_rows() == 0) {
        return false;
    }
    return rez.has_affected_rows();
}
bool BD_Connection::updateKid(string nr, string nume_copil, string prenume_copil, int varsta, string data_nastere, string nume_copil2, int id_tutore)
{
    try {
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
           UPDATE Copii
           SET nume_copil = ?,
               prenume_copil = ?,
               varsta_copil = ?,
               data_nastere_copil = ?,
               ID_Tutore = ?
               WHERE ID_Copil = ? 
        )");

        const std::string u1 = nume_copil;
        const std::string u2 = prenume_copil;
        const int u3 = varsta;
        const std::string u4 = data_nastere;
        const int u5 = id_tutore;
        const int u6 = getnamekid(nume_copil2);

        stmt.bind(0, u1.c_str());
        stmt.bind(1, u2.c_str());
        stmt.bind(2, &u3);
        stmt.bind(3, u4.c_str());
        stmt.bind(4, &u5);
        stmt.bind(5, &u6);

        nanodbc::result rez = stmt.execute();
        if (rez.affected_rows() == 0) {
            return false;
        }

        return rez.has_affected_rows();

    }
    catch (nanodbc::database_error err) {
        cout << err.what();
    }

}
bool BD_Connection::updateHealth(string nr, string nume_boala, string perioada_temperatura, string ora_consultatie_medic, string concluzie_medic, string analize, string rezultate_analize, string lista_vaccinuri, string nume_copil)
{
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
            UPDATE Boli
                SET nume_boala = ?,
                    periaoda_temperatura = ?,
                    ora_consultatie_medic = ?,
                    concluzie_medic = ?,
                    analize = ? ,
                    rezultate_analize = ? ,
                    lista_vaccinuri = ?
            WHERE ID_Copil = ?;
        )");

    const std::string u1 = nume_boala;
    const std::string u2 = perioada_temperatura;
    const std::string u3 = ora_consultatie_medic;
    const std::string u4 = concluzie_medic;
    const std::string u5 = analize;
    const std::string u6 = rezultate_analize;
    const std::string u7 = lista_vaccinuri;
    const int u8 = getnamekid(nume_copil);

    stmt.bind(0, u1.c_str());
    stmt.bind(1, u2.c_str());
    stmt.bind(2, u3.c_str());
    stmt.bind(3, u4.c_str());
    stmt.bind(4, u5.c_str());
    stmt.bind(5, u6.c_str());
    stmt.bind(6, u7.c_str());
    stmt.bind(7, &u8);

    nanodbc::result rez = stmt.execute();
    if (rez.affected_rows() == 0) {
        return false;
    }
    return rez.has_affected_rows();

}
bool BD_Connection::updateFood(string nr, string tip_hrana, int cantitate_hrana, string moment_hranire, string nume_copil)
{
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
           UPDATE Hraniri
                SET tip_hrana = ? ,
                    cantitate_hrana = ? ,
                    moment_hranire = ?
                WHERE ID_Copil = ?;
        )");

    const std::string u1 = tip_hrana;
    const int u2 = cantitate_hrana;
    const std::string u3 = moment_hranire;
    const int u4 = getnamekid(nume_copil);

    stmt.bind(0, u1.c_str());
    stmt.bind(1, &u2);
    stmt.bind(2, u3.c_str());
    stmt.bind(3, &u4);


    nanodbc::result rez = stmt.execute();
    if (rez.affected_rows() == 0) {
        return false;
    }

    return rez.has_affected_rows();
}
bool BD_Connection::updateSize(string nr, int dimenziune_cap, int inaltime, int greutate, string nume_copil)
{
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
            UPDATE Monitorizari_Crestere
                SET dimensiune_cap = ?,
                    inaltime = ?,
                    greutate = ?
                WHERE ID_Copil = ?;
        )");

    const int u1 = dimenziune_cap;
    const int u2 = inaltime;
    const int u3 = greutate;
    const int u4 = getnamekid(nume_copil);

    stmt.bind(0, &u1);
    stmt.bind(1, &u2);
    stmt.bind(2, &u3);
    stmt.bind(3, &u4);

    nanodbc::result rez = stmt.execute();
    if (rez.affected_rows() == 0) {
        return false;
    }
    return rez.has_affected_rows();
}
bool BD_Connection::updateSleep(string nr, string interval_orar, string nume_copil)
{
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
            UPDATE Ore_Somn
                SET interval_orar_somn = ?
                WHERE ID_Copil = ? ;
        )");

    const std::string u1 = interval_orar;
    const int u2 = getnamekid(nume_copil);

    stmt.bind(0, u1.c_str());
    stmt.bind(1, &u2);


    nanodbc::result rez = stmt.execute();
    if (rez.affected_rows() == 0) {
        return false;
    }
    return rez.has_affected_rows();
}
bool BD_Connection::deleteAccount(string nr, string username, string parola) {
    try{
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
           DELETE FROM Tutori WHERE username = ? AND parola = ?;
        )");
        const std::string u1 = username;
        const std::string u2 = parola;
        stmt.bind(0, u1.c_str());
        stmt.bind(1, u2.c_str());

       
        nanodbc::result rez = stmt.execute();
        if (rez.affected_rows() == 0) {
            return false;
        }
        int col = rez.columns();
        while (rez.next()) {
            for (int i = 0; i < col; i++) {
                if (rez.get<string>(i) == username && rez.get<string>(i) == parola)
                {

                    return rez.has_affected_rows();
                }


            }
        }
        

    }
    catch (nanodbc::database_error err) {
        cout << err.what();
    }
        
   
    
}
