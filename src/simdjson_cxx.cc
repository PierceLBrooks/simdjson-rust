#include "include/simdjson_cxx.h"

namespace ffi
{
    int get_int()
    {
        return 1;
    }

    template <typename Output, typename Func>
    Output check(Func func, ErrorCode &code)
    {
        Output output;
        func().tie(output, code);
        return output;
    }

    template <typename Output, typename Func>
    std::unique_ptr<Output> check_unique_ptr(Func func, ErrorCode &code)
    {
        Output output;
        func().tie(output, code);
        return std::make_unique<Output>(std::move(output));
    }

    // ondemand::parser
    std::unique_ptr<OndemandParser> ondemand_parser_new(size_t max_capacity)
    {
        return std::make_unique<OndemandParser>(max_capacity);
    }

    std::unique_ptr<OndemandDocument> ondemand_parser_iterate(OndemandParser &p, const PaddedString &ps, ErrorCode &code)
    {
        return check_unique_ptr<OndemandDocument>(
            [&]
            { return p.iterate(ps); },
            code);
    }

    // ondemand::document
    std::unique_ptr<OndemandObject> ondemand_document_get_object(OndemandDocument &doc, ErrorCode &code)
    {
        // OndemandObject obj;
        // doc.get_object().tie(obj, code);
        // return std::make_unique<OndemandObject>(std::move(obj));
        return check_unique_ptr<OndemandObject>([&]
                                                { return doc.get_object(); },
                                                code);
    }

    std::unique_ptr<OndemandValue> ondemand_document_at_pointer(OndemandDocument &doc, const rust::Str json_pointer, ErrorCode &code)
    {
        // OndemandValue value;
        // doc.at_pointer(std::string_view(json_pointer.data(), json_pointer.size())).tie(value, code);
        // return std::make_unique<OndemandValue>(std::move(value));
        return check_unique_ptr<OndemandValue>([&]
                                               { return doc.at_pointer(std::string_view(json_pointer.data(), json_pointer.size())); },
                                               code);
    }
    std::unique_ptr<OndemandValue> ondemand_document_find_field(OndemandDocument &doc, const rust::Str key, ErrorCode &code)
    {
        OndemandValue value;
        doc.find_field(std::string_view(key.data(), key.size())).tie(value, code);
        return std::make_unique<OndemandValue>(std::move(value));
    }
    std::unique_ptr<OndemandValue> ondemand_document_find_field_unordered(OndemandDocument &doc, const rust::Str key, ErrorCode &code)
    {
        OndemandValue value;
        doc.find_field_unordered(std::string_view(key.data(), key.size())).tie(value, code);
        return std::make_unique<OndemandValue>(std::move(value));
    }

    // ondemand::value
    uint64_t ondemand_value_get_uint64(OndemandValue &value, ErrorCode &code)
    {
        uint64_t v;
        value.get_uint64().tie(v, code);
        return v;
    }
    std::unique_ptr<OndemandArray> ondemand_value_get_array(OndemandValue &value, ErrorCode &code)
    {
        OndemandArray arr;
        value.get_array().tie(arr, code);
        return std::make_unique<OndemandArray>(std::move(arr));
    }
    std::unique_ptr<OndemandObject> ondemand_value_get_object(OndemandValue &value, ErrorCode &code)
    {
        OndemandObject obj;
        value.get_object().tie(obj, code);
        return std::make_unique<OndemandObject>(std::move(obj));
    }
    std::unique_ptr<OndemandValue> ondemand_value_find_field(OndemandValue &value, const rust::Str key, ErrorCode &code)
    {
        OndemandValue v;
        value.find_field(std::string_view(key.data(), key.size())).tie(v, code);
        return std::make_unique<OndemandValue>(std::move(v));
    }
    std::unique_ptr<OndemandValue> ondemand_value_find_field_unordered(OndemandValue &value, const rust::Str key, ErrorCode &code)
    {
        OndemandValue v;
        value.find_field_unordered(std::string_view(key.data(), key.size())).tie(value, code);
        return std::make_unique<OndemandValue>(std::move(v));
    }

    // ondemand::object
    std::unique_ptr<OndemandValue> ondemand_object_at_pointer(OndemandObject &obj, const rust::Str json_pointer, ErrorCode &code)
    {
        OndemandValue v;
        obj.at_pointer(std::string_view(json_pointer.data(), json_pointer.size())).tie(v, code);
        return std::make_unique<OndemandValue>(std::move(v));
    }

    std::unique_ptr<OndemandObjectIterator> ondemand_object_begin(OndemandObject &arr, ErrorCode &code)
    {
        OndemandObjectIterator iter;
        arr.begin().tie(iter, code);
        return std::make_unique<OndemandObjectIterator>(std::move(iter));
    }

    std::unique_ptr<OndemandObjectIterator> ondemand_object_end(OndemandObject &arr, ErrorCode &code)
    {
        OndemandObjectIterator iter;
        arr.end().tie(iter, code);
        return std::make_unique<OndemandObjectIterator>(std::move(iter));
    }
    rust::Str ondemand_object_raw_json(OndemandObject &obj, ErrorCode &code)
    {
        std::string_view rv;
        obj.raw_json().tie(rv, code);
        return rust::Str(rv.data(), rv.size());
    }

    // ondemand::object_iterator
    bool ondemand_object_iterator_not_equal(const OndemandObjectIterator &lhs, const OndemandObjectIterator &rhs)
    {
        return lhs != rhs;
    }
    OndemandObjectIterator &ondemand_object_iterator_next(OndemandObjectIterator &iter)
    {
        return ++iter;
    }
    std::unique_ptr<OndemandField> ondemand_object_iterator_get(OndemandObjectIterator &iter, ErrorCode &code)
    {
        OndemandField field;
        (*iter).tie(field, code);
        // OndemandValue value;
        // std::tie(key, value) = field;
        return std::make_unique<OndemandField>(std::move(field));
    }

    // ondemand::array
    std::unique_ptr<OndemandArrayIterator> ondemand_array_begin(OndemandArray &arr, ErrorCode &code)
    {
        OndemandArrayIterator iter;
        arr.begin().tie(iter, code);
        return std::make_unique<OndemandArrayIterator>(std::move(iter));
    }
    std::unique_ptr<OndemandArrayIterator> ondemand_array_end(OndemandArray &arr, ErrorCode &code)
    {
        OndemandArrayIterator iter;
        arr.end().tie(iter, code);
        return std::make_unique<OndemandArrayIterator>(std::move(iter));
    }
    std::unique_ptr<OndemandValue> ondemand_array_at(OndemandArray &arr, size_t index, ErrorCode &code)
    {
        OndemandValue v;
        arr.at(index).tie(v, code);
        return std::make_unique<OndemandValue>(std::move(v));
    }

    // ondemand::array_iterator
    bool ondemand_array_iterator_equal(const OndemandArrayIterator &lhs, const OndemandArrayIterator &rhs)
    {
        return lhs == rhs;
    }
    bool ondemand_array_iterator_not_equal(const OndemandArrayIterator &lhs, const OndemandArrayIterator &rhs)
    {
        return lhs != rhs;
    }
    OndemandArrayIterator &ondemand_array_iterator_next(OndemandArrayIterator &iter)
    {
        return ++iter;
    }
    std::unique_ptr<OndemandValue> ondemand_array_iterator_get(OndemandArrayIterator &iter, ErrorCode &code)
    {
        OndemandValue v;
        (*iter).tie(v, code);
        return std::make_unique<OndemandValue>(std::move(v));
    }

    // ondemand::field
    rust::Str ondemand_field_unescaped_key(OndemandField &field, ErrorCode &code)
    {
        std::string_view sv;
        field.unescaped_key().tie(sv, code);
        return rust::Str(sv.data(), sv.size());
    }
    std::unique_ptr<OndemandValue> ondemand_field_value(OndemandField &field)
    {
        return std::make_unique<OndemandValue>(std::move(field.value()));
    }

    std::unique_ptr<OndemandRawJsonString> ondemand_field_key(const OndemandField &field)
    {
        return std::make_unique<OndemandRawJsonString>(std::move(field.key()));
    }

    // ondemand::raw_json_string
    // rust::Str ondemand_raw_json_string_unescape(const OndemandRawJsonString &rjs, OndemandValue v, ErrorCode &code) {
    //     auto sv = rjs.unesacpe
    // }

    // padded_string
    std::unique_ptr<PaddedString> padded_string_load(const std::string &filename, ErrorCode &code)
    {
        PaddedString ps;
        PaddedString::load(filename).tie(ps, code);
        return std::make_unique<PaddedString>(std::move(ps));
    }

    std::unique_ptr<PaddedString> padded_string_from_str(const rust::Str s)
    {

        return std::make_unique<PaddedString>(s.data(), s.size());
    }

} // namespace ffi
