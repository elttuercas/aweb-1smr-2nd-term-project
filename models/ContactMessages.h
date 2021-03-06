/**
 *
 *  ContactMessages.h
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <json/json.h>
#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

using namespace drogon::orm;
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
    namespace sqlite3
    {

        class ContactMessages
        {
        public:
            struct Cols
            {
                static const std::string _id;
                static const std::string _name;
                static const std::string _surname;
                static const std::string _message;
                static const std::string _submission_ts;
                static const std::string _hash;
                static const std::string _email;
            };

            const static int                   primaryKeyNumber;
            const static std::string           tableName;
            const static bool                  hasPrimaryKey;
            const static std::string           primaryKeyName;
            using PrimaryKeyType = uint64_t;
            const PrimaryKeyType &getPrimaryKey() const;

            /**
             * @brief constructor
             * @param r One row of records in the SQL query result.
             * @param indexOffset Set the offset to -1 to access all columns by column names,
             * otherwise access all columns by offsets.
             * @note If the SQL is not a style of 'select * from table_name ...' (select all
             * columns by an asterisk), please set the offset to -1.
             */
            explicit ContactMessages(const Row &r, const ssize_t indexOffset = 0) noexcept;

            /**
             * @brief constructor
             * @param pJson The json object to construct a new instance.
             */
            explicit ContactMessages(const Json::Value &pJson) noexcept(false);

            /**
             * @brief constructor
             * @param pJson The json object to construct a new instance.
             * @param pMasqueradingVector The aliases of table columns.
             */
            ContactMessages(const Json::Value &pJson,
                            const std::vector<std::string> &pMasqueradingVector) noexcept(false);

            ContactMessages() = default;

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
            const uint64_t &getValueOfId() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<uint64_t> &getId() const noexcept;

            ///Set the value of the column id
            void setId(const uint64_t &pId) noexcept;


            /**  For column name  */
            ///Get the value of the column name, returns the default value if the column is null
            const std::string &getValueOfName() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<std::string> &getName() const noexcept;

            ///Set the value of the column name
            void setName(const std::string &pName) noexcept;
            void setName(std::string &&pName) noexcept;


            /**  For column surname  */
            ///Get the value of the column surname, returns the default value if the column is null
            const std::string &getValueOfSurname() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<std::string> &getSurname() const noexcept;

            ///Set the value of the column surname
            void setSurname(const std::string &pSurname) noexcept;
            void setSurname(std::string &&pSurname) noexcept;


            /**  For column message  */
            ///Get the value of the column message, returns the default value if the column is null
            const std::string &getValueOfMessage() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<std::string> &getMessage() const noexcept;

            ///Set the value of the column message
            void setMessage(const std::string &pMessage) noexcept;
            void setMessage(std::string &&pMessage) noexcept;


            /**  For column submission_ts  */
            ///Get the value of the column submission_ts, returns the default value if the column is null
            const uint64_t &getValueOfSubmissionTs() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<uint64_t> &getSubmissionTs() const noexcept;

            ///Set the value of the column submission_ts
            void setSubmissionTs(const uint64_t &pSubmissionTs) noexcept;


            /**  For column hash  */
            ///Get the value of the column hash, returns the default value if the column is null
            const std::string &getValueOfHash() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<std::string> &getHash() const noexcept;

            ///Set the value of the column hash
            void setHash(const std::string &pHash) noexcept;
            void setHash(std::string &&pHash) noexcept;


            /**  For column email  */
            ///Get the value of the column email, returns the default value if the column is null
            const std::string &getValueOfEmail() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<std::string> &getEmail() const noexcept;

            ///Set the value of the column email
            void setEmail(const std::string &pEmail) noexcept;
            void setEmail(std::string &&pEmail) noexcept;


            static size_t getColumnNumber() noexcept
            { return 7; }

            static const std::string &getColumnName(size_t index) noexcept(false);

            Json::Value toJson() const;
            Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;
            /// Relationship interfaces
        private:
            friend Mapper<ContactMessages>;
            static const std::vector<std::string> &insertColumns() noexcept;
            void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
            const std::vector<std::string> updateColumns() const;
            void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
            ///For mysql or sqlite3
            void updateId(const uint64_t id);
            std::shared_ptr<uint64_t>          id_;
            std::shared_ptr<std::string>       name_;
            std::shared_ptr<std::string>       surname_;
            std::shared_ptr<std::string>       message_;
            std::shared_ptr<uint64_t>          submissionTs_;
            std::shared_ptr<std::string>       hash_;
            std::shared_ptr<std::string>       email_;
            struct MetaData
            {
                const std::string colName_;
                const std::string colType_;
                const std::string colDatabaseType_;
                const ssize_t     colLength_;
                const bool        isAutoVal_;
                const bool        isPrimaryKey_;
                const bool        notNull_;
            };
            static const std::vector<MetaData> metaData_;
            bool                               dirtyFlag_[7] = {false};
        public:
            static const std::string &sqlForFindingByPrimaryKey()
            {
                static const std::string sql = "select * from " + tableName + " where id = ?";
                return sql;
            }

            static const std::string &sqlForDeletingByPrimaryKey()
            {
                static const std::string sql = "delete from " + tableName + " where id = ?";
                return sql;
            }

            std::string sqlForInserting(bool &needSelection) const
            {
                std::string sql             = "insert into " + tableName + " (";
                size_t      parametersCount = 0;
                needSelection = false;
                if (dirtyFlag_[1])
                {
                    sql += "name,";
                    ++parametersCount;
                }
                if (dirtyFlag_[2])
                {
                    sql += "surname,";
                    ++parametersCount;
                }
                if (dirtyFlag_[3])
                {
                    sql += "message,";
                    ++parametersCount;
                }
                if (dirtyFlag_[4])
                {
                    sql += "submission_ts,";
                    ++parametersCount;
                }
                if (dirtyFlag_[5])
                {
                    sql += "hash,";
                    ++parametersCount;
                }
                if (dirtyFlag_[6])
                {
                    sql += "email,";
                    ++parametersCount;
                }
                if (parametersCount > 0)
                {
                    sql[sql.length() - 1] = ')';
                    sql += " values (";
                }
                else
                    sql += ") values (";

                if (dirtyFlag_[1])
                {
                    sql.append("?,");

                }
                if (dirtyFlag_[2])
                {
                    sql.append("?,");

                }
                if (dirtyFlag_[3])
                {
                    sql.append("?,");

                }
                if (dirtyFlag_[4])
                {
                    sql.append("?,");

                }
                if (dirtyFlag_[5])
                {
                    sql.append("?,");

                }
                if (dirtyFlag_[6])
                {
                    sql.append("?,");

                }
                if (parametersCount > 0)
                {
                    sql.resize(sql.length() - 1);
                }
                sql.append(1, ')');
                LOG_TRACE << sql;
                return sql;
            }
        };
    } // namespace sqlite3
} // namespace drogon_model
