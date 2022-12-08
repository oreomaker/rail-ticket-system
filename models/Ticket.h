/**
 *
 *  Ticket.h
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#pragma once
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#ifdef __cpp_impl_coroutine
#include <drogon/orm/CoroMapper.h>
#endif
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <json/json.h>
#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

namespace drogon
{
namespace orm
{
class DbClient;
using DbClientPtr = std::shared_ptr<DbClient>;
}
}
namespace drogon_model
{
namespace rail_ticket
{

class Ticket
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _trip;
        static const std::string _seatType;
        static const std::string _carriage;
        static const std::string _seatPosition;
        static const std::string _available;
        static const std::string _startStation;
        static const std::string _endStation;
    };

    const static int primaryKeyNumber;
    const static std::string tableName;
    const static bool hasPrimaryKey;
    const static std::string primaryKeyName;
    using PrimaryKeyType = int32_t;
    const PrimaryKeyType &getPrimaryKey() const;

    /**
     * @brief constructor
     * @param r One row of records in the SQL query result.
     * @param indexOffset Set the offset to -1 to access all columns by column names,
     * otherwise access all columns by offsets.
     * @note If the SQL is not a style of 'select * from table_name ...' (select all
     * columns by an asterisk), please set the offset to -1.
     */
    explicit Ticket(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit Ticket(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    Ticket(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    Ticket() = default;

    void updateByJson(const Json::Value &pJson) noexcept(false);
    void updateByMasqueradedJson(const Json::Value &pJson,
                                 const std::vector<std::string> &pMasqueradingVector) noexcept(false);
    static bool validateJsonForCreation(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForCreation(const Json::Value &,
                                                const std::vector<std::string> &pMasqueradingVector,
                                                    std::string &err);
    static bool validateJsonForUpdate(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForUpdate(const Json::Value &,
                                          const std::vector<std::string> &pMasqueradingVector,
                                          std::string &err);
    static bool validJsonOfField(size_t index,
                          const std::string &fieldName,
                          const Json::Value &pJson,
                          std::string &err,
                          bool isForCreation);

    /**  For column id  */
    ///Get the value of the column id, returns the default value if the column is null
    const int32_t &getValueOfId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getId() const noexcept;
    ///Set the value of the column id
    void setId(const int32_t &pId) noexcept;

    /**  For column trip  */
    ///Get the value of the column trip, returns the default value if the column is null
    const std::string &getValueOfTrip() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getTrip() const noexcept;
    ///Set the value of the column trip
    void setTrip(const std::string &pTrip) noexcept;
    void setTrip(std::string &&pTrip) noexcept;

    /**  For column seatType  */
    ///Get the value of the column seatType, returns the default value if the column is null
    const int8_t &getValueOfSeattype() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int8_t> &getSeattype() const noexcept;
    ///Set the value of the column seatType
    void setSeattype(const int8_t &pSeattype) noexcept;

    /**  For column carriage  */
    ///Get the value of the column carriage, returns the default value if the column is null
    const int8_t &getValueOfCarriage() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int8_t> &getCarriage() const noexcept;
    ///Set the value of the column carriage
    void setCarriage(const int8_t &pCarriage) noexcept;

    /**  For column seatPosition  */
    ///Get the value of the column seatPosition, returns the default value if the column is null
    const std::string &getValueOfSeatposition() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getSeatposition() const noexcept;
    ///Set the value of the column seatPosition
    void setSeatposition(const std::string &pSeatposition) noexcept;
    void setSeatposition(std::string &&pSeatposition) noexcept;

    /**  For column available  */
    ///Get the value of the column available, returns the default value if the column is null
    const int32_t &getValueOfAvailable() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getAvailable() const noexcept;
    ///Set the value of the column available
    void setAvailable(const int32_t &pAvailable) noexcept;

    /**  For column startStation  */
    ///Get the value of the column startStation, returns the default value if the column is null
    const std::string &getValueOfStartstation() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getStartstation() const noexcept;
    ///Set the value of the column startStation
    void setStartstation(const std::string &pStartstation) noexcept;
    void setStartstation(std::string &&pStartstation) noexcept;
    void setStartstationToNull() noexcept;

    /**  For column endStation  */
    ///Get the value of the column endStation, returns the default value if the column is null
    const std::string &getValueOfEndstation() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getEndstation() const noexcept;
    ///Set the value of the column endStation
    void setEndstation(const std::string &pEndstation) noexcept;
    void setEndstation(std::string &&pEndstation) noexcept;
    void setEndstationToNull() noexcept;


    static size_t getColumnNumber() noexcept {  return 8;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;
    /// Relationship interfaces
  private:
    friend drogon::orm::Mapper<Ticket>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<Ticket>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> id_;
    std::shared_ptr<std::string> trip_;
    std::shared_ptr<int8_t> seattype_;
    std::shared_ptr<int8_t> carriage_;
    std::shared_ptr<std::string> seatposition_;
    std::shared_ptr<int32_t> available_;
    std::shared_ptr<std::string> startstation_;
    std::shared_ptr<std::string> endstation_;
    struct MetaData
    {
        const std::string colName_;
        const std::string colType_;
        const std::string colDatabaseType_;
        const ssize_t colLength_;
        const bool isAutoVal_;
        const bool isPrimaryKey_;
        const bool notNull_;
    };
    static const std::vector<MetaData> metaData_;
    bool dirtyFlag_[8]={ false };
  public:
    static const std::string &sqlForFindingByPrimaryKey()
    {
        static const std::string sql="select * from " + tableName + " where id = ?";
        return sql;
    }

    static const std::string &sqlForDeletingByPrimaryKey()
    {
        static const std::string sql="delete from " + tableName + " where id = ?";
        return sql;
    }
    std::string sqlForInserting(bool &needSelection) const
    {
        std::string sql="insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
            sql += "id,";
            ++parametersCount;
        if(dirtyFlag_[1])
        {
            sql += "trip,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "seatType,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "carriage,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "seatPosition,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "available,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "startStation,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "endStation,";
            ++parametersCount;
        }
        needSelection=true;
        if(parametersCount > 0)
        {
            sql[sql.length()-1]=')';
            sql += " values (";
        }
        else
            sql += ") values (";

        sql +="default,";
        if(dirtyFlag_[1])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[2])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[3])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[4])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[5])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[6])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[7])
        {
            sql.append("?,");

        }
        if(parametersCount > 0)
        {
            sql.resize(sql.length() - 1);
        }
        sql.append(1, ')');
        LOG_TRACE << sql;
        return sql;
    }
};
} // namespace rail_ticket
} // namespace drogon_model
