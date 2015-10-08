/******************************************************************************
 * Copyright (C) 2014 by Ralf Kaestner                                        *
 * ralf.kaestner@gmail.com                                                    *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#include <variant_topic_tools/BuiltinSerializer.h>
#include <variant_topic_tools/BuiltinTypeTraits.h>
#include <variant_topic_tools/BuiltinVariant.h>

namespace variant_topic_tools {

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

template <typename T>
BuiltinDataType::ImplT<T>::ImplT(const std::string& identifier) :
  BuiltinDataType::Impl(identifier) {
  BOOST_STATIC_ASSERT(!ros::message_traits::IsMessage<T>::value);
}

template <typename T>
BuiltinDataType::ImplT<T>::~ImplT() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

template <typename T>
const std::type_info& BuiltinDataType::ImplT<T>::getTypeInfo() const {
  return typeid(T);
}

template <typename T>
size_t BuiltinDataType::ImplT<T>::getSize() const {
  return ros::message_traits::template isFixedSize<T>() ? sizeof(T) : 0;
}

template <typename T>
bool BuiltinDataType::ImplT<T>::isFixedSize() const {
  return ros::message_traits::template isFixedSize<T>();
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

template <typename T> BuiltinDataType BuiltinDataType::create(const
    std::string& identifier) {
  BuiltinDataType dataType;
  
  dataType.impl.reset(new boost::shared_ptr<DataType::Impl>(
    new ImplT<T>(identifier)));
  
  return dataType;
}

template <typename T>
Serializer BuiltinDataType::ImplT<T>::createSerializer(const DataType& type)
    const {
  return BuiltinSerializer::template create<T>();
}

template <typename T>
Variant BuiltinDataType::ImplT<T>::createVariant(const DataType& type) const {
  return BuiltinVariant::template create<T>(type);
}

}
