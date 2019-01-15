#ifndef XDMFWRITER_HPP
#define XDMFWRITER_HPP

#include <string>

#include <hdf5.h>
#include <mpi.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "hdfwriter.hpp"
#include "types.hpp"

namespace pt = boost::property_tree;

class XDMFWriter: public HDFWriter {
public:
  XDMFWriter(std::string filespec, const MPI_Comm& comm);
  ~XDMFWriter();

  void write_image(const Image& image);

  void write_map(const Map& map);

  static const std::string writer_name;
  static const std::vector<std::string> extensions;

protected:
  int rank;
  std::string xdmf_filename;
  std::string xdmf_groupname;
  pt::ptree xdmf_tree;

  static std::string h5name_from_xdmfname(const std::string &filename);

private:
  void prepopulate_xdmf_ptree();
};

#endif // XDMFWRITER_HPP
