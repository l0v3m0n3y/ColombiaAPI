#ifndef COLOMBIA_API_H
#define COLOMBIA_API_H

#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <pplx/pplx.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace web;
using namespace web::http;
using namespace web::http::client;

class ColombiaAPI {
private:
    std::string api_base = "https://api-colombia.com/api/v1";
    http_client_config client_config;
    
    http_request create_request(const std::string& endpoint, const std::string& method) {
        http_request request;
        
        if (method == "GET") {
            request.set_method(methods::GET);
        } else if (method == "POST") {
            request.set_method(methods::POST);
        } else if (method == "PUT") {
            request.set_method(methods::PUT);
        } else if (method == "DEL") {
            request.set_method(methods::DEL);
        }
        
        request.set_request_uri(utility::conversions::to_string_t(endpoint));
        request.headers().add(U("Host"), U("api-colombia.com"));
        request.headers().add(U("Content-Type"), U("application/json"));
        request.headers().add(U("User-Agent"), U("Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/115.0"));
        
        return request;
    }
    
    pplx::task<json::value> make_api_call(const std::string& endpoint, const std::string& method) {
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        auto request = create_request(endpoint, method);

        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: ") + utility::conversions::to_string_t(std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: ") + utility::conversions::to_string_t(e.what()));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

public:
    ColombiaAPI() {
        client_config.set_validate_certificates(false);
    }

    pplx::task<json::value> get_country_info() {
        return make_api_call("/Country/Colombia", "GET");
    }

    pplx::task<json::value> get_country_president() {
        return make_api_call("/Country/President", "GET");
    }

    pplx::task<json::value> get_all_departments() {
        return make_api_call("/Department", "GET");
    }

    pplx::task<json::value> get_department_by_id(int departmentId) {
        return make_api_call("/Department/" + std::to_string(departmentId), "GET");
    }

    pplx::task<json::value> get_department_by_name(const std::string& departmentName) {
        return make_api_call("/Department/name/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(departmentName))), "GET");
    }

    pplx::task<json::value> get_department_cities(int departmentId) {
        return make_api_call("/Department/" + std::to_string(departmentId) + "/cities", "GET");
    }

    pplx::task<json::value> get_department_natural_areas(int departmentId) {
        return make_api_call("/Department/" + std::to_string(departmentId) + "/naturalareas", "GET");
    }

    pplx::task<json::value> get_department_tourist_attractions(int departmentId) {
        return make_api_call("/Department/" + std::to_string(departmentId) + "/touristicattractions", "GET");
    }

    pplx::task<json::value> get_department_presidents(int departmentId) {
        return make_api_call("/Department/" + std::to_string(departmentId) + "/presidents", "GET");
    }

    pplx::task<json::value> get_department_region(int departmentId) {
        return make_api_call("/Department/" + std::to_string(departmentId) + "/region", "GET");
    }

    pplx::task<json::value> get_all_cities() {
        return make_api_call("/City", "GET");
    }

    pplx::task<json::value> get_city_by_id(int cityId) {
        return make_api_call("/City/" + std::to_string(cityId), "GET");
    }

    pplx::task<json::value> get_city_by_name(const std::string& cityName) {
        return make_api_call("/City/name/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(cityName))), "GET");
    }

    pplx::task<json::value> get_city_department(int cityId) {
        return make_api_call("/City/" + std::to_string(cityId) + "/department", "GET");
    }

    pplx::task<json::value> get_city_president(int cityId) {
        return make_api_call("/City/" + std::to_string(cityId) + "/president", "GET");
    }

    pplx::task<json::value> get_city_tourist_attractions(int cityId) {
        return make_api_call("/City/" + std::to_string(cityId) + "/touristicattractions", "GET");
    }

    pplx::task<json::value> get_all_regions() {
        return make_api_call("/Region", "GET");
    }

    pplx::task<json::value> get_region_by_id(int regionId) {
        return make_api_call("/Region/" + std::to_string(regionId), "GET");
    }

    pplx::task<json::value> get_region_by_name(const std::string& regionName) {
        return make_api_call("/Region/name/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(regionName))), "GET");
    }

    pplx::task<json::value> get_region_departments(int regionId) {
        return make_api_call("/Region/" + std::to_string(regionId) + "/departments", "GET");
    }

    pplx::task<json::value> get_region_natural_areas(int regionId) {
        return make_api_call("/Region/" + std::to_string(regionId) + "/naturalareas", "GET");
    }

    pplx::task<json::value> get_region_tourist_attractions(int regionId) {
        return make_api_call("/Region/" + std::to_string(regionId) + "/touristicattractions", "GET");
    }

    pplx::task<json::value> get_all_presidents() {
        return make_api_call("/President", "GET");
    }

    pplx::task<json::value> get_president_by_id(int presidentId) {
        return make_api_call("/President/" + std::to_string(presidentId), "GET");
    }

    pplx::task<json::value> get_president_by_name(const std::string& presidentName) {
        return make_api_call("/President/name/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(presidentName))), "GET");
    }

    pplx::task<json::value> get_all_tourist_attractions() {
        return make_api_call("/TouristicAttraction", "GET");
    }

    pplx::task<json::value> get_tourist_attraction_by_id(int attractionId) {
        return make_api_call("/TouristicAttraction/" + std::to_string(attractionId), "GET");
    }

    pplx::task<json::value> get_tourist_attraction_by_name(const std::string& attractionName) {
        return make_api_call("/TouristicAttraction/name/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(attractionName))), "GET");
    }

    pplx::task<json::value> get_tourist_attraction_by_city(int cityId) {
        return make_api_call("/TouristicAttraction/city/" + std::to_string(cityId), "GET");
    }

    pplx::task<json::value> get_tourist_attraction_by_department(int departmentId) {
        return make_api_call("/TouristicAttraction/department/" + std::to_string(departmentId), "GET");
    }

    pplx::task<json::value> get_tourist_attraction_by_region(int regionId) {
        return make_api_call("/TouristicAttraction/region/" + std::to_string(regionId), "GET");
    }

    pplx::task<json::value> get_all_natural_areas() {
        return make_api_call("/NaturalArea", "GET");
    }

    pplx::task<json::value> get_natural_area_by_id(int areaId) {
        return make_api_call("/NaturalArea/" + std::to_string(areaId), "GET");
    }

    pplx::task<json::value> get_natural_area_by_name(const std::string& areaName) {
        return make_api_call("/NaturalArea/name/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(areaName))), "GET");
    }

    pplx::task<json::value> get_natural_area_by_department(int departmentId) {
        return make_api_call("/NaturalArea/department/" + std::to_string(departmentId), "GET");
    }

    pplx::task<json::value> get_natural_area_by_region(int regionId) {
        return make_api_call("/NaturalArea/region/" + std::to_string(regionId), "GET");
    }

    pplx::task<json::value> get_natural_area_by_type(const std::string& areaType) {
        return make_api_call("/NaturalArea/type/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(areaType))), "GET");
    }

    pplx::task<json::value> get_all_airports() {
        return make_api_call("/Airport", "GET");
    }

    pplx::task<json::value> get_airport_by_id(int airportId) {
        return make_api_call("/Airport/" + std::to_string(airportId), "GET");
    }

    pplx::task<json::value> get_airport_by_name(const std::string& airportName) {
        return make_api_call("/Airport/name/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(airportName))), "GET");
    }

    pplx::task<json::value> get_all_radios() {
        return make_api_call("/Radio", "GET");
    }

    pplx::task<json::value> get_radio_by_id(int radioId) {
        return make_api_call("/Radio/" + std::to_string(radioId), "GET");
    }

    pplx::task<json::value> get_radio_by_name(const std::string& radioName) {
        return make_api_call("/Radio/name/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(radioName))), "GET");
    }

    pplx::task<json::value> get_all_tv_channels() {
        return make_api_call("/TvChannel", "GET");
    }

    pplx::task<json::value> get_tv_channel_by_id(int channelId) {
        return make_api_call("/TvChannel/" + std::to_string(channelId), "GET");
    }

    pplx::task<json::value> get_tv_channel_by_name(const std::string& channelName) {
        return make_api_call("/TvChannel/name/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(channelName))), "GET");
    }

    pplx::task<json::value> get_country_map() {
        return make_api_call("/Map/Country", "GET");
    }

    pplx::task<json::value> get_department_map(int departmentId) {
        return make_api_call("/Map/Department/" + std::to_string(departmentId), "GET");
    }

    pplx::task<json::value> get_city_map(int cityId) {
        return make_api_call("/Map/City/" + std::to_string(cityId), "GET");
    }

    pplx::task<json::value> search_all(const std::string& searchTerm) {
        return make_api_call("/Search/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(searchTerm))), "GET");
    }

    pplx::task<json::value> search_cities(const std::string& searchTerm) {
        return make_api_call("/Search/City/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(searchTerm))), "GET");
    }

    pplx::task<json::value> search_departments(const std::string& searchTerm) {
        return make_api_call("/Search/Department/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(searchTerm))), "GET");
    }

    pplx::task<json::value> search_regions(const std::string& searchTerm) {
        return make_api_call("/Search/Region/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(searchTerm))), "GET");
    }

    pplx::task<json::value> search_tourist_attractions(const std::string& searchTerm) {
        return make_api_call("/Search/TouristicAttraction/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(searchTerm))), "GET");
    }

    pplx::task<json::value> search_natural_areas(const std::string& searchTerm) {
        return make_api_call("/Search/NaturalArea/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(searchTerm))), "GET");
    }

    pplx::task<json::value> search_presidents(const std::string& searchTerm) {
        return make_api_call("/Search/President/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(searchTerm))), "GET");
    }

    pplx::task<json::value> search_airports(const std::string& searchTerm) {
        return make_api_call("/Search/Airport/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(searchTerm))), "GET");
    }
};

#endif
