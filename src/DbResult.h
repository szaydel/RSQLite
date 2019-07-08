#ifndef __RSQLITE_SQLITE_RESULT__
#define __RSQLITE_SQLITE_RESULT__

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>


class DbConnection;
typedef boost::shared_ptr<DbConnection> DbConnectionPtr;

class SqliteResultImpl;
typedef SqliteResultImpl DbResultImpl;

class DbResult : boost::noncopyable {
  DbConnectionPtr pConn_;
  boost::scoped_ptr<DbResultImpl> impl;

public:
  DbResult(const DbConnectionPtr& pConn, const std::string& sql);
  ~DbResult();

public:
  static DbResult* create_and_send_query(const DbConnectionPtr& con, const std::string& sql, bool is_statement);

public:
  bool complete() const;
  bool is_active() const;
  int n_rows_fetched();
  int n_rows_affected();

  void bind(const List& params);
  List fetch(int n_max = -1);

  List get_column_info();

public:
  CharacterVector get_placeholder_names() const;

private:
  void validate_params(const List& params) const;
};

#endif
